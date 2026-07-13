# MP3 Tag Reader

##  Overview

The MP3 Tag Reader is a command-line application developed in C that reads and displays metadata stored in MP3 files using the ID3v2 tag format. The program extracts information such as title, artist, album, year, genre, and comments.

---

##  Features

- Read MP3 ID3v2 tags
- Display Title
- Display Artist
- Display Album
- Display Year
- Display Genre
- Display Comments
- Command-line interface

---

## Technologies Used

- C Programming
- File Handling
- Binary File Processing
- Structures
- Modular Programming
- Makefile

---

##  Project Structure

```
main.c
read.c
view.c
edit.c
mp3tag.h
types.h
Makefile
```

---

##  How to Compile

```bash
make
```

or

```bash
gcc *.c -o mp3tagreader
```

---

##  Run

Display MP3 information:

```bash
./mp3tagreader song.mp3
```

or

```bash
./a.out song.mp3
```

---

## Sample Output

```
-----------------------------------------
MP3 TAG INFORMATION
-----------------------------------------

Title    : Shape of You
Artist   : Ed Sheeran
Album    : Divide
Year     : 2017
Genre    : Pop
Comment  : Sample MP3 File

-----------------------------------------
```

---

##  Concepts Used

- File Handling
- Binary File Reading
- Structures
- Command-Line Arguments
- ID3v2 Tag Parsing
- String Manipulation

---

##  Future Improvements

- Edit MP3 tags
- Support ID3v1 and ID3v2
- Batch processing
- GUI application
- Album artwork extraction
