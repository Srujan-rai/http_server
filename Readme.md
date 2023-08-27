# Multi-Threaded HTTP Server

This is a multi-threaded HTTP server implemented in C++ that can handle incoming HTTP requests concurrently. It serves a simple "Hello, World!" message in response to incoming requests.

## Author Information

- **Author:** [SRUJAN_RAI]
- **UB#:** [4SF21CI047]
- **Email Address:** [srujan.ci21@sahyadri.edu.in]

## Table of Contents

- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Compiling the Server](#compiling-the-server)
- [Running the Server](#running-the-server)
- [Stopping the Server](#stopping-the-server)
- [Server Configuration](#server-configuration)
- [Testing](#testing)
- [Contributing](#contributing)
- [License](#license)

## Getting Started

### Prerequisites

Before you can run the server, make sure you have the following prerequisites installed:

- g++ compiler (for C++ code)
- pthread library (for multi-threading)

### Compiling the Server

To compile the server, follow these steps:

1. Open a terminal window.

2. Navigate to the project directory where the source code is located.

3. Run the following command:

   ```bash
   g++ -o myserver myserver.cpp -lpthread
