## **YouTube Video/Playlist Downloader**

A powerful and user-friendly Python script designed to download YouTube videos or entire playlists in your preferred quality, directly to your computer. This cross-platform tool is compatible with Windows, Linux, and macOS, making it accessible for all users.

### **Features**

- **Download Single Videos**: Easily download individual YouTube videos by providing their URL.
- **Download Playlists**: Download entire YouTube playlists or choose specific videos from a playlist.
- **Choose Video Quality**: Select from multiple video quality options (Best, High, Medium, Low).
- **Cross-Platform Compatibility**: Works seamlessly on Windows, Linux, and macOS.

### **Dependencies**

To run this script, the following dependencies are required:

- **Python 3.x**: Ensure Python 3 is installed on your system.
- **yt-dlp**: A command-line tool to download videos from YouTube and other sites.
- **ffmpeg**: A multimedia framework for handling video, audio, and other multimedia files and streams.

### **Installation Guide**

#### 1. **Python 3.x Installation**

Make sure Python 3.x is installed on your system. You can verify by running:

```bash
python3 --version
```

If Python is not installed, download and install it from [Python's official website](https://www.python.org/downloads/).

#### 2. **Installing `yt-dlp`**

`yt-dlp` is the tool used for downloading YouTube videos and playlists.

**On Windows, Linux, and macOS:**

```bash
pip install yt-dlp
```

Alternatively, on Linux, you can use:

```bash
sudo apt-get install yt-dlp
```

#### 3. **Installing `ffmpeg`**

`ffmpeg` is required to process video and audio streams, especially for higher quality downloads.

**Windows:**

1. Download the latest `ffmpeg` release from [ffmpeg.org](https://ffmpeg.org/download.html).
2. Extract the downloaded archive.
3. Add the `bin` directory of `ffmpeg` to your system's PATH.

**Linux:**

```bash
sudo apt-get install ffmpeg
```

**macOS:**

Using Homebrew:

```bash
brew install ffmpeg
```

### **How to Use the Script**

1. **Clone or Download the Script**: Save the script (`app.py`) to a directory on your system.

2. **Run the Script**:

   Open your terminal (Command Prompt on Windows, Terminal on macOS/Linux) and navigate to the directory where the script is located. Run the script using Python:

   ```bash
   python3 app.py
   ```

3. **Follow the Prompts**:

   - **Enter the URL**: You’ll be prompted to enter the URL of the YouTube video or playlist you want to download.
   - **Select Playlist or Single Video**: If it’s a playlist, you’ll be asked whether you want to download the entire playlist or select specific videos.
   - **Choose Quality**: Select the quality of the video (Best, High, Medium, Low).
   - **Download**: The script will download the selected video(s) and save them to your `Downloads` folder.

### **Examples**

#### Example 1: Downloading a Single Video

```bash
python3 app.py
```
- Enter the URL of the YouTube video: `https://youtu.be/W13gbCLVU40`
- Select the desired video quality (e.g., 2 for High 1080p).
- The video will be downloaded and saved to your `Downloads` folder.

#### Example 2: Downloading an Entire Playlist

```bash
python3 app.py
```
- Enter the URL of the YouTube playlist: `https://www.youtube.com/playlist?list=PLxwbQuwnqw4fFmABIFU_xFP-Sp5DKW-b2`
- Choose `y` when asked if you want to download the entire playlist.
- Select the desired video quality (e.g., 1 for Best quality).
- The entire playlist will be downloaded to your `Downloads` folder.

#### Example 3: Downloading Specific Videos from a Playlist

```bash
python3 app.py
```
- Enter the URL of the YouTube playlist: `https://www.youtube.com/playlist?list=PLxwbQuwnqw4fFmABIFU_xFP-Sp5DKW-b2`
- Choose `n` when asked if you want to download the entire playlist.
- Enter the numbers corresponding to the videos you want to download (e.g., `1, 3, 5`).
- Select the desired video quality.
- The selected videos will be downloaded to your `Downloads` folder.

### **Troubleshooting**

- **Network Errors**: Ensure your internet connection is stable.
- **Permission Issues**: Make sure you have write permissions to the `Downloads` directory.
- **Missing Dependencies**: Verify that `yt-dlp` and `ffmpeg` are installed correctly and accessible via your system's PATH.

### **License**

This script is provided under the MIT License. You are free to use, modify, and distribute this script.

### **Contribution**

Feel free to submit issues or contribute to the script by opening a pull request on the [GitHub repository](#).

