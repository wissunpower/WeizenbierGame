```mermaid
sequenceDiagram
    Client->>Server: system.middleman().spawn_client()
    Client->>Server: LoginRequest
    Server->>Client: LoginResponse
```