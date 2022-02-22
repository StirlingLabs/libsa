using System.Diagnostics.CodeAnalysis;
using System.Runtime.CompilerServices;
using StirlingLabs.Native;
using StirlingLabs.Utilities;
using static StirlingLabs.sockaddr;

namespace StirlingLabs;

[SuppressMessage("Design", "CA1045", Justification = "Hacks")]
public static unsafe class SockaddrExtensions
{
    public static bool Free(ref this sockaddr self)
    {
        var p = (sockaddr*)Unsafe.AsPointer(ref Unsafe.AsRef(self));
        if (p == null)
            return false;
        sa_free(p);
        return true;
    }

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    internal static sockaddr* AsPointer(ref this sockaddr r)
        => (sockaddr*)Unsafe.AsPointer(ref r);

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static ref sockaddr AsRef(ref this sockaddr r) => ref r;

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static bool IsIPv4(ref this sockaddr self)
        => sa_is_ipv4(self.AsPointer());

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static bool IsIPv6(ref this sockaddr self)
        => sa_is_ipv6(self.AsPointer());

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static void SetPort(ref this sockaddr self, ushort value)
    {
        if (!sa_set_port(self.AsPointer(), value))
            throw new ArgumentOutOfRangeException(nameof(value));
    }

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static ushort GetPort(ref this sockaddr self)
    {
        var port = sa_get_port(self.AsPointer());
        return checked((ushort)port);
    }

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static void SetScope(ref this sockaddr self, ushort value)
    {
        var pSa = self.AsPointer();
        if (!pSa->TrySetScopeIndex(value))
            throw new ArgumentOutOfRangeException(nameof(value));
    }

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static ushort GetScope(ref this sockaddr self)
    {
        var pSa = self.AsPointer();
        var port = pSa->GetScopeNoThrow();
        return checked((ushort)port);
    }

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static int GetScopeNoThrow(ref this sockaddr self)
        => sa_get_scope_index(self.AsPointer());

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    private static bool TrySetScopeIndex(ref this sockaddr self, ushort value)
        => sa_set_scope_index(self.AsPointer(), value);

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static SockaddrAddressBytes* GetAddressBytes(ref this sockaddr self)
        => (SockaddrAddressBytes*)self.AsPointer();

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static void SetScopeByName(ref this sockaddr self, Utf8String value)
    {
        if (!sa_set_scope(self.AsPointer(), value.Pointer))
            throw new ArgumentException("Invalid Scope", nameof(value));
    }

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static Utf8String GetScopeName(ref this sockaddr self)
        => new(sa_get_scope(self.AsPointer()));

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static int GetHashCode(ref this sockaddr self)
        => ((IntPtr)self.AsPointer()).GetHashCode();

    private static readonly ConditionalWeakTable<string, CleanUpAction> StringCache = new();

    [SuppressMessage("Reliability", "CA2000", Justification = "Intentional")]
    public static string? ToString(ref this sockaddr self)
    {
        void AddCleanUp1(string addressStr, Utf8String address)
        {
            if (!address.IsInterned)
                StringCache.Add(addressStr, new(() => {
                    sa_free(address.Pointer);
                }));
        }

        void AddCleanUp2(string addressStr, Utf8String address, Utf8String scope)
        {
            if (address.IsInterned)
                return;

            if (!scope.IsInterned)
                StringCache.Add(addressStr, new(() => {
                    sa_free(address.Pointer);
                    sa_free(scope.Pointer);
                }));
            else
                StringCache.Add(addressStr, new(() => {
                    sa_free(address.Pointer);
                }));
        }

        var pSa = self.AsPointer();
        if (pSa == null) return null;

        var address = pSa->GetAddressString();
        if (address == default) return null;

        var addressStr = address.ToString();
        if (addressStr == null) return null;

        if (pSa->IsIPv6())
        {
            var scope = pSa->GetScopeName();
            if (scope == default)
            {
                AddCleanUp1(addressStr, address);
                var scopeIndex = pSa->GetScope();
                return scopeIndex != 0
                    ? $"{address}:{pSa->GetPort()}%{scopeIndex}"
                    : $"{address}:{pSa->GetPort()}";
            }

            AddCleanUp2(addressStr, address, scope);
            return $"{address}:{pSa->GetPort()}%{scope}";
        }

        AddCleanUp1(addressStr, address);
        return $"{address}:{pSa->GetPort()}";
    }

    public static Utf8String GetAddressString(ref this sockaddr self)
    {
        var sa = self.AsPointer();

        return sa == null
            ? default
            : new Utf8String(sa_address_to_str(sa));

    }
}
