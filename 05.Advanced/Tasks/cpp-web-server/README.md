# C++ Web Server

## Project Structure

```plaintext
cpp-web-server/
├── includes/          # Header files
│   ├── request.h
│   ├── response.h
│   ├── router.h
│   └── server.h
├── src/               # Source files
│   ├── main.cpp
│   ├── request.cpp
│   ├── response.cpp
│   ├── router.cpp
│   └── server.cpp
├── config/            # Configuration files
│   └── server.config
├── public/            # Directory for HTML files
│   └── index.html
├── .editorconfig      # Editor configuration
├── Makefile           # Makefile for building the project
├── README.md          # Project documentation
└── .gitignore         # Git ignore file
```

## Building the Project

### Compiler and Flags

- `CXX`: The variable for the C++ compiler.
- `CXXFLAGS`: Contains the flags passed to the C++ compiler:
  - `-Wall`: Enables all the warnings about constructions that some users consider questionable.
  - `-Wextra`: Enables additional warning flags that are not enabled by `-Wall`.
  - `-Iincludes`: Tells the compiler to add the `includes` directory to the list of directories to be searched for header files.
  - `-std=c++11`: Specifies the C++ standard to be used.

### Directories

- `SRCDIR`: The directory containing the source files.
- `INCDIR`: The directory containing the header files.
- `BUILDDIR`: The directory where object files will be stored.
- `BINDIR`: The directory where the final executable will be placed.
- `TARGET`: The final executable file to be built.

### Source and Object Files

- `SOURCES`: Contains all the `.cpp` files in the `SRCDIR` directory.
- `OBJECTS`: Derived from `SOURCES` by replacing the source directory prefix and `.cpp` extension with the build directory prefix and `.o` extension.

### Makefile

This Makefile compiles and links the C++ source files to build the web server.

#### Important Variables

- `CXX` and `CXXFLAGS`: Compiler and its flags.
- `SRCDIR`, `INCDIR`, `BUILDDIR`, `BINDIR`: Directories for source, includes, build objects, and binary respectively.
- `SOURCES` and `OBJECTS`: Lists of source and object files.

#### Key Rules

- `$(TARGET)`: Links object files to create the executable.
- `$(BUILDDIR)/%.o`: Compiles source files into object files.
- `$(BUILDDIR)` and `$(BINDIR)`: Create necessary directories if they do not exist.
- `clean`: Removes generated files.

### Building the Project

To build the project, run the following command:

```sh
make
```

### Running the Server

To run the server, execute the built binary:

```sh
./bin/webserver
```

## Server Implementation

The server is implemented using a basic class structure with `Server`, `Request`, `Response`, and `Router` classes.

### Server

The `Server` class is responsible for setting up the server, listening for incoming connections, and handling client requests.

### Request

The `Request` class parses HTTP requests.

### Response

The `Response` class constructs HTTP responses.

### Router

The `Router` class handles routing of requests to appropriate responses.

### Utilities

Utility functions such as `readFile` are provided to help with common tasks like reading files.

## Configuration

You can modify the server configuration in `config/server.config`.

## HTML Files

Place your HTML files in the `public` directory. For example, `public/index.html` can be accessed via `http://127.0.0.1:8080/`.

### Example `index.html`

Create an `index.html` file in the `public` directory with the following content:

```html
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Simple Web Server</title>
  </head>
  <body>
    <h1>Hello, World!</h1>
  </body>
</html>
```

## Testing the Server

### Using `netcat`

1. **Start the server**:

   ```sh
   ./bin/webserver
   ```

2. **Open another terminal and connect using `netcat`**:

   ```sh
   nc 127.0.0.1 8080
   ```

3. **Send an HTTP GET request**:

   ```sh
   GET / HTTP/1.1
   Host: 127.0.0.1
   ```

4. **Press Enter twice**. You should see the HTML response from the server.

### Using `telnet`

1. **Start the server**:

   ```sh
   ./bin/webserver
   ```

2. **Open another terminal and connect using `telnet`**:

   ```sh
   telnet 127.0.0.1 8080
   ```

3. **Send an HTTP GET request**:

   ```sh
   GET / HTTP/1.1
   Host: 127.0.0.1
   ```

4. **Press Enter twice**. You should see the HTML response from the server.

### Using a Request File

1. **Create the request file `request.txt`**:

   ```sh
   echo -e "GET / HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n" > request.txt
   ```

2. **Send the request using `nc`**:

   ```sh
   nc 127.0.0.1 8080 < request.txt
   ```

## License

This project is licensed under the GNU General Public License v3.0. See the `LICENSE` file for details.
