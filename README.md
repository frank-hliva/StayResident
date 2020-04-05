# StayResident

The application uses normal executables like windows services

## Motivation

Developing windows services was little bit more difficult than creation normal applications for me. And i don't liked them, because it was boring. I needed something for manage running apps in a background on my server, something what runs crashed app again.

## Using

You have to edit `App.toml` file, for example:

```toml
[Startup]
	paths = [
		'c:\totalcmd\TOTALCMD64.EXE',
		'c:\windows\NOTEPAD.EXE'
	]
```
  
And after you need to start `StayResident.exe`
