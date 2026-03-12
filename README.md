# PLAYA 🎵

**PLAYA** is a lightweight **TUI (Terminal User Interface) music player written in C**.
It scans a folder for MP3 files, lets you select songs using the keyboard, and displays ASCII visualizations while the music plays.

---

## Features

* 🎧 MP3 playback using `mpg123`
* 📂 Automatic music folder scanning
* ⌨️ Keyboard navigation
* 📊 ASCII visualizer
* ⏱ Music progress bar with time
* 🖥 Responsive terminal UI with `ncurses`

---

## Controls

| Key   | Action             |
| ----- | ------------------ |
| ↑ / ↓ | Navigate songs     |
| Enter | Play selected song |
| q     | Quit               |

---

## Requirements

* `gcc`
* `ncurses`
* `mpg123`
* `ffmpeg` (for duration detection)

Install dependencies:

```bash
sudo apt install build-essential libncurses5-dev mpg123 ffmpeg
```

---

## Build

```bash
gcc *.c -I../include -lncursesw -o playa
```

---

## Run

Create a `music` folder and place MP3 files inside:

```
playa/
 ├─ playa
 ├─ music/
 │   ├─ song1.mp3
 │   ├─ song2.mp3
 │   └─ song3.mp3
```

Run:

```bash
./playa
```

---

## Preview

```
PLAYA

> song1.mp3
  song2.mp3
  song3.mp3

[██████░░░░░░░░░░░░░░] 01:12 / 03:45
```

---

## Tech Stack

* C
* ncurses
* mpg123
* ffprobe

---

## Future Improvements

* real audio spectrum visualizer
* shuffle / repeat
* volume control
* playlist support
* WAV / FLAC support
