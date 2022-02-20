using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;
using System.Runtime.CompilerServices;
using NUnit.Framework;
using StirlingLabs.Utilities;
using StirlingLabs;

namespace StirlingLabs.Sockaddr.Tests;

public class Tests
{
    //private static Utf8String _ipv4LocalhostStr = Utf8String.Create("127.0.0.1");
    //private static Utf8String _ipv6LocalhostStr = Utf8String.Create("::1");

    public static IEnumerable IPv4TestCases
    {
        get {
            yield return new object[] { "127.0.0.1", (ushort)1000 };
            yield return new object[] { "1.2.3.4", (ushort)1234 };
            yield return new object[] { "4.3.2.1", (ushort)4321 };
        }
    }

    public static IEnumerable IPv6TestCases
    {
        get {
            yield return new object[] { "::1", (ushort)1000, (ushort)0 };
            yield return new object[] { "::1.2.3.4", (ushort)1234, (ushort)1 };
            yield return new object[] { "::4.3.2.1", (ushort)4321, (ushort)1 };
            yield return new object[] { "::1", (ushort)1000, (ushort)1 };
            yield return new object[] { "2001:db8::8a2e:370", (ushort)1, (ushort)3 };
            yield return new object[] { "::ffff:192.0.2.128", (ushort)2, (ushort)2 };
            yield return new object[] { "64:ff9b::c000:280", (ushort)3, (ushort)1 };
        }
    }

    [TestCaseSource(nameof(IPv4TestCases))]
    [SuppressMessage("Warning", "CS1718", Justification = "Yes")]
    public unsafe void ReferenceEqualityIPv4Tests(string address, ushort port)
    {
        var pSa1 = sockaddr.CreateIPv4(address, port);
        var pSa2 = sockaddr.CreateIPv4(address, port);
        ref var sa1 = ref pSa1->AsRef();
        ref var sa2 = ref pSa2->AsRef();

        Assert.False(sa1.Equals(sa2));
        Assert.True(sa1.Equals(sa1));
        Assert.True(sa2.Equals(sa2));
        Assert.False(sa1.Equals(null));
        Assert.False(sa2.Equals(null));

        Assert.False(sa1 == sa2);
        // ReSharper disable once EqualExpressionComparison
        Assert.True(sa1 == sa1);
        // ReSharper disable once EqualExpressionComparison
        Assert.True(sa2 == sa2);

        Assert.False(sa1 == null);
        Assert.False(sa2 == null);

        Assert.True(sa1 != sa2);
        // ReSharper disable once EqualExpressionComparison
        Assert.False(sa1 != sa1);
        // ReSharper disable once EqualExpressionComparison
        Assert.False(sa2 != sa2);

        Assert.True(sa1 != null);
        Assert.True(sa2 != null);

        Assert.AreEqual((nuint)Unsafe.AsPointer(ref sa1), (nuint)pSa1);
        Assert.AreEqual((nuint)Unsafe.AsPointer(ref sa2), (nuint)pSa2);

        Assert.True(sa1.Equals(pSa1));
        Assert.True(sa2.Equals(pSa2));
    }


    [TestCaseSource(nameof(IPv6TestCases))]
    [SuppressMessage("Warning", "CS1718", Justification = "Yes")]
    public unsafe void ReferenceEqualityIPv6Tests(string address, ushort port, ushort scope)
    {
        var pSa1 = sockaddr.CreateIPv6(address, port, scope);
        var pSa2 = sockaddr.CreateIPv6(address, port, scope);
        ref var sa1 = ref pSa1->AsRef();
        ref var sa2 = ref pSa2->AsRef();

        Assert.False(sa1.Equals(sa2));
        Assert.True(sa1.Equals(sa1));
        Assert.True(sa2.Equals(sa2));
        Assert.False(sa1.Equals(null));
        Assert.False(sa2.Equals(null));

        Assert.False(sa1 == sa2);
        // ReSharper disable once EqualExpressionComparison
        Assert.True(sa1 == sa1);
        // ReSharper disable once EqualExpressionComparison
        Assert.True(sa2 == sa2);

        Assert.False(sa1 == null);
        Assert.False(sa2 == null);

        Assert.True(sa1 != sa2);
        // ReSharper disable once EqualExpressionComparison
        Assert.False(sa1 != sa1);
        // ReSharper disable once EqualExpressionComparison
        Assert.False(sa2 != sa2);

        Assert.True(sa1 != null);
        Assert.True(sa2 != null);

        Assert.AreEqual((nuint)Unsafe.AsPointer(ref sa1), (nuint)pSa1);
        Assert.AreEqual((nuint)Unsafe.AsPointer(ref sa2), (nuint)pSa2);

        Assert.True(sa1.Equals(pSa1));
        Assert.True(sa2.Equals(pSa2));
    }

    [TestCaseSource(nameof(IPv4TestCases))]
    public unsafe void StringMemberIPv4Tests(string address, ushort port)
    {
        var pSa = sockaddr.CreateIPv4(address, port);

        Assert.True(pSa->IsIPv4());
        Assert.False(pSa->IsIPv6());
        Assert.True(pSa->IsIPv4);
        Assert.False(pSa->IsIPv6);

        Assert.AreEqual(address, pSa->GetAddressString().ToString());

        Assert.AreEqual(port, pSa->GetPort());

        Assert.AreEqual($"{address}:{port}", pSa->ToString());

        ref var sa = ref pSa->AsRef();

        Assert.True(sa.IsIPv4());
        Assert.False(sa.IsIPv6());
        Assert.True(sa.IsIPv4);
        Assert.False(sa.IsIPv6);

        Assert.AreEqual(address, sa.GetAddressString().ToString());

        Assert.AreEqual(port, sa.GetPort());

        Assert.AreEqual($"{address}:{port}", sa.ToString());
    }

    [TestCaseSource(nameof(IPv6TestCases))]
    public unsafe void StringMemberIPv6Tests(string address, ushort port, ushort scope)
    {
        var pSa = sockaddr.CreateIPv6(address, port, scope);

        Assert.True(pSa->IsIPv6());
        Assert.False(pSa->IsIPv4());
        Assert.True(pSa->IsIPv6);
        Assert.False(pSa->IsIPv4);

        Assert.AreEqual(address, pSa->GetAddressString().ToString());

        Assert.AreEqual(port, pSa->GetPort());

        Assert.AreEqual(scope, pSa->GetScope());

        if (scope == 0)
            Assert.AreEqual($"{address}:{port}", pSa->ToString());
        else
        {
            var scopeName = sockaddr.GetNameOfScope(scope);
            Assert.AreEqual(scopeName == default
                    ? $"{address}:{port}%{scope}"
                    : $"{address}:{port}%{scopeName}",
                pSa->ToString());
        }

        ref var sa = ref pSa->AsRef();

        Assert.True(sa.IsIPv6());
        Assert.False(sa.IsIPv4());
        Assert.True(sa.IsIPv6);
        Assert.False(sa.IsIPv4);

        Assert.AreEqual(address, sa.GetAddressString().ToString());

        Assert.AreEqual(port, sa.GetPort());

        if (scope == 0)
            Assert.AreEqual($"{address}:{port}", pSa->ToString());
        else
        {
            var scopeName = sockaddr.GetNameOfScope(scope);
            Assert.AreEqual(scopeName == default
                    ? $"{address}:{port}%{scope}"
                    : $"{address}:{port}%{scopeName}",
                sa.ToString());
        }
    }
}
