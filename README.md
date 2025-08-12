# Simple Jarvis Documentation

## Overview

For practical purposes, this project has none. The only help I can give for those hoping to use ChatGPT in an efficient manner is to navigate you to `https://chatgpt.com/`. 

However, as a learning exercise, this project was of great use. It taught me how to connect the ChatGPT backend to a Windows application's frontend. I learned about local sockets, QT Creator GUI creation, the art of creating a deployable program, and the joys of documenting one's process. 

I hope you enjoy (and if you are so willing, contribute to making this project better -- so I can also learn more!).

[Example Image](example.png)

## Table of Contents
- [Overview](#overview)
- [Installation](#installation)
- [Contributing](#contributing)
- [My Process](#my-process)

## Installation

1. **Install Python**
   Make sure you have **Python 3.9.19** installed on your system. You can verify with:

   ```bash
   python --version
   ```

2. **Set up a virtual environment**
   From the project root, create and activate a virtual environment (example using `venv`):

   ```bash
   python -m venv venv
   # On Windows:
   venv\Scripts\activate
   # On macOS/Linux:
   source venv/bin/activate
   ```

3. **Install dependencies**
   Install all required packages from `requirements.txt`:

   ```bash
   pip install -r requirements.txt
   ```

4. **Obtain an OpenAI API key**

   * Visit [OpenAI API Keys](https://platform.openai.com/settings/organization/api-keys)
   * Create a new key or copy an existing one.

5. **Configure your API key**
   Open `jarvisbackend/jarvisbackend/chat_api.py` and paste your API key in the appropriate variable or configuration section.

6. **Run the application**
   Start the backend by running:

   ```bash
   run.bat
   ```

## Contributing

All contributions are welcome! Fix a bug (there are many), make the GUI prettier, or do whatever your heart fancies. !

To get started on this project, you can follow these steps.
1. Fork this repository.
2. Create a branch: `git checkout -b my-feature`
3. Make your changes and commit them: `git commit -m 'Add new feature'`
4. Push to your fork and submit a pull request.

Here are a list of edits that should be implemented, but which I haven't gotten around to yet:

 - Storing and fetching API credentials from a `.env` file.
 - Adding a clear error when the user hasn't attached their API key
 - Gracefully handling network errors for the API
 - Make the frontend GUI prettier.

## My Process

I had to install QT Creator (and use my 10-day free trial) to work on
the C++ GUI.

Getting the ChatGPT API up-and-running was very straightforward.

Initially, I thought QT Creator was only a programmatic
creator. After tinkering around with QT, I learned that there's also
a visual creation tool, similar to the interface for Google Slides.

I'm having some trouble now incorporating the "Network" module into QT Creator.

I've hit a wall with trying to import `QNetworkAccessManager`. Let me  see if I can diagnose the problem. I figured it out with the help of
ChatGPT -- I had to add "Network" to the part of my CMake file that
had `target_link_libraries`.

Huzzah! I was successfully able to send a request from my QT Creator application to my Python backend. It's cool to learn about how applications on the same device interact through network sockets, even if it's a "local" socket. 

I'm trying to create a "stream" of 
communication between the GUI
and the Python backend so that I can
send multiple requests back and forth on one connection. This way,
the backend can send a response when the message is recieved, 
and again with the actual message.

I'm having some issues right now testing the new Python
backend that streams data in chunks, instead of just
sending out one big packet. When I'm doing my testing,
both packets send at the same time if I use `iter_content`
and make the chunk size too large. If I use `iter_lines`, the program still just spits out both responses at once.

I just want some way for the user to know that the message was recieved while they're waiting.

I got a working version using simple HTTP requests, but then I tried to implement streaming and the code stopped working. The lesson that should be gleamed from this is: as soon as you have a working version, save it somewhere. I wish I could just switch GitHub branches and go back to the old working version. 

Dune was right, beginnings are such delicate times. It's so much better to start a project out right and stay the course, then decide to go a different route later on and have a lot of side-effects.

I'm having some trouble figuring out how to make a Release build in QT Creator.

I'm still trying to create a Release build for my QT Creator App. I need to make one before
my subscription runs out, and so that I can present it on my portfolio.

This is where I'm stuck: I build the project in Release mode. I go to the build folder with the .exe. I use windeployqt.exe on it, but then I get an error saying that Jarvis-QT.exe is not a QT executable.

One clue as to why I may be getting this error is that windeployqt.exe isn't in my QT directory's Tools folder: 
It's in my anaconda folder -- this makes sense why it doesn't have access to the correct DLLs to build my .exe.

I'm trying to use the windeployqt.exe help information to get this project going. I've added my QT binary directory to my PATH, but I still can't run windeployqt.exe on the binary -- it still says that it doesn't recognze the binary as a QT file.

I found out the issue. I thought that the windeployqt.exe that I needed was in my anaconda folder because I couldn't find any file called windeployqt in my QT binary folder. Turns out that I was looking in the wrong QT binary folder: the actual QT binary folder had the correct windeployqt.exe, and when I ran it on my application's binary, it worked! The lesson to be learned from this is, when working with computer paths, knowing exactly where something is, and not where you think it should be, is crucial. This is the command that I got to work: `C:\QT\6.9.1\mingw_64\bin\windeployqt.exe .\Jarvis-QT.exe`.

Now I need a way to package all the code together.

I think, of the parts of the project that I should know about, I have the least experience with deploying the code.

I'm starting to realize that when you're building something new, most of the time you're going
to be troubleshooting and reading documentation -- not building.

I ran into an issue when using `pyinstaller`. When Django first runs an application, it creates a smaller program, then reloads the program. But when running from an executable, it's unable to reload the program. To work around this, I had to add an argument to my entry-point function: `execute_from_command_line(["manage.py", "runserver", "127.0.0.1:8000", "--noreload"])`. This way, the program wouldn't have to reload, and thus the server can be launched form my .py file.

(May these notes be a helpful guide to any future readers!)