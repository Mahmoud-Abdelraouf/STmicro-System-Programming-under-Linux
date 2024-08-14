import os
from yt_dlp import YoutubeDL

def list_videos_in_playlist(url):
    ydl_opts = {
        'quiet': True,
        'extract_flat': True,  # Extract metadata without downloading
        'force_generic_extractor': True
    }
    with YoutubeDL(ydl_opts) as ydl:
        info_dict = ydl.extract_info(url, download=False)
        return info_dict

def download_youtube_video(url, selected_format, selected_videos=None):
    ydl_opts = {
        'format': selected_format,
        'outtmpl': os.path.expanduser('~/Downloads/%(title)s.%(ext)s'),
    }
    
    with YoutubeDL(ydl_opts) as ydl:
        if selected_videos is None:
            # Download the entire video or all videos in the playlist
            ydl.download([url])
        else:
            # Download only the selected videos from the playlist
            for video in selected_videos:
                ydl.download([video['url']])

if __name__ == "__main__":
    print("\n" + "-" * 50)
    print(" YOUTUBE VIDEO/PLAYLIST DOWNLOADER ".center(50))
    print("-" * 50 + "\n")
    
    video_url = input("Enter the URL of the YouTube video or playlist: ")

    # Add message to tell the user to wait while checking the URL
    print("\nChecking if the URL is a playlist... Please wait.\n")

    # Check if the URL is a playlist
    info_dict = list_videos_in_playlist(video_url)
    if 'entries' in info_dict:
        print("\n" + "-" * 50)
        print(" PLAYLIST DETECTED ".center(50))
        print("-" * 50 + "\n")
        
        # Ask if the user wants to download the entire playlist or just one video
        download_choice = input("Do you want to download the entire playlist? (y/n): ").strip().lower()

        if download_choice == 'y':
            selected_videos = None  # This means all videos in the playlist will be downloaded
        else:
            # List videos in the playlist and allow user to choose
            print("\nAvailable videos in the playlist:")
            print("-" * 50)
            for i, entry in enumerate(info_dict['entries']):
                print(f"{i + 1}. {entry['title']}")
            print("-" * 50)
            
            video_indices = input("\nEnter the numbers of the videos you want to download (e.g., 1, 3, 5): ")
            selected_indices = [int(x.strip()) - 1 for x in video_indices.split(',')]
            selected_videos = [info_dict['entries'][i] for i in selected_indices]
    else:
        print("This is not a playlist URL. Proceeding to download the video directly.")
        selected_videos = None  # Proceed with single video download

    # Ask the user for the desired quality
    print("\n" + "-" * 50)
    print(" SELECT VIDEO QUALITY ".center(50))
    print("-" * 50)
    print("1. Best")
    print("2. High (1080p)")
    print("3. Medium (720p)")
    print("4. Low (480p)")
    print("-" * 50)
    quality_choice = input("Enter the number corresponding to the desired quality: ")

    # Map the user's choice to a format string
    quality_map = {
        '1': 'bestvideo+bestaudio/best',
        '2': 'bestvideo[height<=1080]+bestaudio/best[height<=1080]',
        '3': 'bestvideo[height<=720]+bestaudio/best[height<=720]',
        '4': 'bestvideo[height<=480]+bestaudio/best[height<=480]'
    }

    # Select the format based on user input
    selected_format = quality_map.get(quality_choice, 'best')

    print("\n" + "-" * 50)
    print(" DOWNLOADING VIDEO ".center(50))
    print("-" * 50 + "\n")

    # Download the selected video(s) or the entire playlist
    download_youtube_video(video_url, selected_format, selected_videos)

    print("\n" + "-" * 50)
    print(" DOWNLOAD COMPLETED ".center(50))
    print("-" * 50 + "\n")
