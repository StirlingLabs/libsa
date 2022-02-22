using System.Collections;
using System.Diagnostics.CodeAnalysis;
using System.Runtime.CompilerServices;

namespace StirlingLabs;

public readonly unsafe struct SockaddrAddressBytes : IEnumerable<byte>
{
    /// <summary>
    /// Accesses or mutates an IP address bytes in network byte order. 
    /// </summary>
    /// <param name="i">The index parameter.</param>
    /// <exception cref="IndexOutOfRangeException">The indexer parameter was out of range.</exception>
    [SuppressMessage("Design", "CA1065")]
    public byte this[int i]
    {
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        get {
            var value = GetByte(i);
            if (value == -1) throw new IndexOutOfRangeException();
            return (byte)value;
        }
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        set {
            if (!TrySetByte(i, value))
                throw new IndexOutOfRangeException();
        }
    }

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public int GetByte(int i)
        => sockaddr.sa_get_address_byte((sockaddr*)Unsafe.AsPointer(ref Unsafe.AsRef(this)), i);

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public bool TrySetByte(int i, byte value)
        => sockaddr.sa_set_address_byte((sockaddr*)Unsafe.AsPointer(ref Unsafe.AsRef(this)), i, value);

    public int Length
    {
        get {
            var p = (sockaddr*)Unsafe.AsPointer(ref Unsafe.AsRef(this));
            return p->IsIPv6() ? 16
                : p->IsIPv4() ? 4
                : 0;
        }
    }

    public IEnumerator<byte> GetEnumerator()
        => new SockaddrAddressBytesEnumerator((sockaddr*)Unsafe.AsPointer(ref Unsafe.AsRef(this)));

    IEnumerator IEnumerable.GetEnumerator()
        => GetEnumerator();
}
