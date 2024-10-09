# Last.fm Top Albums

This project is an experimental application for learning the [POCO library](https://pocoproject.org/).

The goal is to make a request to the [Last.fm API](https://www.last.fm/api) and generate a grid displaying the top albums of a given user.

## Getting Started

Performing a git recursive-clone will get you the latest source:

```sh
git clone --recursive https://github.com/wsilverio/lastfm-top-albums.git
```

### Obtain a Last.fm API Key

Follow the [official instructions](https://www.last.fm/api#getting-started) to obtain the Last.fm API key.

### Building the Project

You can build the project using CMake:

```sh
cmake -B build
cmake --build build
```

## Usage

Run the program by specifying the API key and the desired Last.fm username. Upon successful execution, an image will be generated in the current working directory.

```sh
./build/bin/lastfm-top-albums --api-key=<API_KEY> --username=<USERNAME>
<USERNAME>.jpg written
```
