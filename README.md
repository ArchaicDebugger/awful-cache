# awful-cache

This will be the most awful cache you can ever use but it's a good tool to practice C++.

What I intend to do:

1. Key-value TCP server, stored only in primitive shape
2. Namespace division, optional
3. Basic CLI (will probably become a detached program like redis-cli)
4. High-availability out of the box with automatic failover and failover commands like what Patroni has
5. Persistence layer, FLUSH commands, will try to come up with a creative storage pattern
6. Export/Import functionality
7. Seed from running instance
8. Configurable parallelism - thread pool for the TCP server
9. Prometheus monitoring format for custom frontends
10. Small HTML monitoring page, should use SSL, should do server-side rendering, should handle possible actions
