# StayResident

The application uses executable files like windows services

## Motivation

Developing of windows services was little bit more difficult than creation normal applications for me. And i don't like them, because it is boring. I needed something for manage running apps in background on my server, something what runs crashed apps again.

## Using

You have to edit App.toml file, for example:

```toml
[Startup]
	paths = [
		'c:\totalcmd\TOTALCMD64.EXE',
		'c:\windows\NOTEPAD.EXE'
	]
  
And after you need to start StayResident.exe
