using System.Diagnostics;
using System.Diagnostics.CodeAnalysis;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
#if !NO_INTERNAL_DEPS
using StirlingLabs.Utilities;
#endif

namespace StirlingLabs;

using static SockaddrExtensions;

[SuppressMessage("Design", "CA1066", Justification = "Opaque")]
[SuppressMessage("ReSharper", "InconsistentNaming")]
[SuppressMessage("ReSharper", "InvokeAsExtensionMethod")]
public readonly unsafe struct sockaddr
{
    private const string LibName = "sa";

#if NET5_0_OR_GREATER
    //[SuppressGCTransition]
#endif
    [DllImport(LibName, ExactSpelling = true)]
    internal static extern bool sa_is_ipv4(sockaddr* sa);

#if NET5_0_OR_GREATER
    //[SuppressGCTransition]
#endif
    [DllImport(LibName, ExactSpelling = true)]
    internal static extern bool sa_is_ipv6(sockaddr* sa);

#if NET5_0_OR_GREATER
    [SuppressGCTransition]
#endif
    [DllImport(LibName, ExactSpelling = true)]
    internal static extern sbyte* sa_address_to_str(sockaddr* sa);

#if NET5_0_OR_GREATER
    [SuppressGCTransition]
#endif
    [DllImport(LibName, ExactSpelling = true)]
    internal static extern sockaddr* sa_ipv4(sbyte* str, ushort port);

#if NET5_0_OR_GREATER
    [SuppressGCTransition]
#endif
    [DllImport(LibName, ExactSpelling = true)]
    internal static extern sockaddr* sa_ipv6(sbyte* str, ushort port);

#if NET5_0_OR_GREATER
    [SuppressGCTransition]
#endif
    [DllImport(LibName, ExactSpelling = true)]
    internal static extern int sa_get_port(sockaddr* sa);

#if NET5_0_OR_GREATER
    [SuppressGCTransition]
#endif
    [DllImport(LibName, ExactSpelling = true)]
    internal static extern bool sa_set_port(sockaddr* sa, ushort port);

#if NET5_0_OR_GREATER
    [SuppressGCTransition]
#endif
    [DllImport(LibName, ExactSpelling = true)]
    internal static extern sbyte* sa_get_scope(sockaddr* sa);

#if NET5_0_OR_GREATER
    [SuppressGCTransition]
#endif
    [DllImport(LibName, ExactSpelling = true)]
    internal static extern bool sa_set_scope(sockaddr* sa, sbyte* scope);

#if NET5_0_OR_GREATER
    [SuppressGCTransition]
#endif
    [DllImport(LibName, ExactSpelling = true)]
    internal static extern int sa_get_scope_index(sockaddr* sa);

#if NET5_0_OR_GREATER
    [SuppressGCTransition]
#endif
    [DllImport(LibName, ExactSpelling = true)]
    internal static extern bool sa_set_scope_index(sockaddr* sa, ushort scope);


#if NET5_0_OR_GREATER
    [SuppressGCTransition]
#endif
    [DllImport(LibName, ExactSpelling = true)]
    internal static extern int sa_get_address_byte(sockaddr* sa, int index);

#if NET5_0_OR_GREATER
    [SuppressGCTransition]
#endif
    [DllImport(LibName, ExactSpelling = true)]
    internal static extern bool sa_set_address_byte(sockaddr* sa, int index, byte value);

#if NET5_0_OR_GREATER
    [SuppressGCTransition]
#endif
    [DllImport(LibName, ExactSpelling = true)]
    internal static extern sbyte* sa_scope_get_name(ushort scope);

#if NET5_0_OR_GREATER
    [SuppressGCTransition]
#endif
    [DllImport(LibName, ExactSpelling = true)]
    internal static extern ushort sa_scope_get_index(sbyte* scope);

#if NET5_0_OR_GREATER
    [SuppressGCTransition]
#endif
    [DllImport(LibName, ExactSpelling = true)]
    internal static extern void sa_free(void* p);

    public static sockaddr* CreateIPv4(Utf8String address, ushort port)
    {
        var result = sa_ipv4(address.Pointer, port);
        if (result == null) throw new ArgumentException("Invalid arguments.");
        return result;
    }

    public static sockaddr* CreateIPv6(Utf8String address, ushort port)
    {
        var result = sa_ipv6(address.Pointer, port);
        if (result == null) throw new ArgumentException("Invalid arguments.");
        return result;
    }

    public static sockaddr* CreateIPv6(Utf8String address, ushort port, ushort scope)
    {
        var sa = CreateIPv6(address, port);
        if (scope != 0) sa->SetScope(scope);
        return sa;
    }

    public static sockaddr* CreateIPv6(Utf8String address, ushort port, Utf8String scope)
    {
        var sa = CreateIPv6(address, port);
        if (scope != default) sa->SetScopeByName(scope);
        return sa;
    }

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public override bool Equals(object? obj)
        => false;

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static bool operator ==(in sockaddr left, in sockaddr right)
        => Unsafe.AreSame(ref Unsafe.AsRef(left), ref Unsafe.AsRef(right));

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static bool operator !=(in sockaddr left, in sockaddr right)
        => !(left == right);

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public bool Equals(in sockaddr other)
        => this == other;

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static bool operator ==(in sockaddr left, sockaddr* right)
        => Unsafe.AreSame(ref Unsafe.AsRef(left), ref Unsafe.AsRef<sockaddr>(right));

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static bool operator !=(in sockaddr left, sockaddr* right)
        => !(left == right);

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public bool Equals(sockaddr* other)
        => this == other;

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static Utf8String GetNameOfScope(ushort scope)
        => new(sa_scope_get_name(scope));

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static ushort GetIndexOfScope(Utf8String scope)
        => sa_scope_get_index(scope.Pointer);

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public override string? ToString()
        => SockaddrExtensions.ToString(ref Unsafe.AsRef(this));

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public override int GetHashCode()
        => SockaddrExtensions.GetHashCode(ref Unsafe.AsRef(this));

    public bool IsIPv4
    {
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        get => SockaddrExtensions.IsIPv4(ref Unsafe.AsRef(this));
    }

    public bool IsIPv6
    {
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        get => SockaddrExtensions.IsIPv6(ref Unsafe.AsRef(this));
    }

    public SockaddrAddressBytes* AddressBytes
    {
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        get => SockaddrExtensions.GetAddressBytes(ref Unsafe.AsRef(this));
    }

    public ushort Port
    {
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        get => SockaddrExtensions.GetPort(ref Unsafe.AsRef(this));
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        set => SockaddrExtensions.SetPort(ref Unsafe.AsRef(this), value);
    }

    public Utf8String ScopeName
    {
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        get => SockaddrExtensions.GetScopeName(ref Unsafe.AsRef(this));
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        set => SockaddrExtensions.SetScopeByName(ref Unsafe.AsRef(this), value);
    }

    public ushort ScopeIndex
    {
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        get => SockaddrExtensions.GetScope(ref Unsafe.AsRef(this));
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        set => SockaddrExtensions.SetScope(ref Unsafe.AsRef(this), value);
    }
}