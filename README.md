![libsa](libsa.jpg)

`libsa` provides cross-platform socket address bindings in C11, designed to be very portable and easy to use.  This allows higher-level network code to use a single format but still communicate effectively with low-level native platform code.

Users are guaranteed big endian (network) byte order of address bytes, so you do not have to worry about byte order for ports and scope indexes regardless of the underlying platform.  `libsa` abstracts away address family values, the location of the address family field, provides sizing information and takes care of allocation and freeing of sockaddr structures on the heap.

### Why reinvent the wheel?

Historically, binding authors have had to work around platform inconsistency in sockaddr or rely on native libraries to manipulate sockaddr via helper functions (e.g. `libuv` has a lot of sockaddr code).  The concept provided by `libsa` is to separate the helper functions from the target library, so it doesn't have to be rewritten every time, yet lets those bindings cooperate effectively.

### Portable

Currently wrapped for:

- C#/.Net by [sockaddr.Net](https://github.com/StirlingLabs/sockaddr.Net)

If you wrap libsa for another language, please create a PR to update this list.

### Future

We intend to expand this to any platform or shape of sockaddr without changing the API, all that should be required is by simply recompiling to the target platform with no special treatment.

### Support

Development of this project is supported by [Stirling Labs](https://stirlinglabs.github.io).
