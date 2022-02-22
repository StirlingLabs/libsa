using System.Collections;
using System.Runtime.CompilerServices;

namespace StirlingLabs;

public class SockaddrAddressBytesEnumerator : IEnumerable<byte>, IEnumerator<byte>
{
    private readonly unsafe SockaddrAddressBytes* _p;

    private int _offset;
    private readonly int _length;
    public unsafe SockaddrAddressBytesEnumerator(SockaddrAddressBytes* p)
    {
        _p = p;
        _offset = -1;
        _length = _p->Length;
    }

    public unsafe SockaddrAddressBytesEnumerator(sockaddr* p) : this((SockaddrAddressBytes*)p) { }


    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public IEnumerator<byte> GetEnumerator() => this;

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    IEnumerator IEnumerable.GetEnumerator() => this;

    public bool MoveNext()
    {
        if (_offset + 1 > _length)
            return false;
        ++_offset;
        return true;
    }

    public void Reset()
        => _offset = -1;

    public unsafe byte Current => checked((byte)_p->GetByte(_offset));

    object IEnumerator.Current => Current;

    public void Dispose() { }
}
