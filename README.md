# StayResident

The application uses normal executables like windows services

## Motivation

Developing windows services was little bit more difficult than creation normal applications for me. And i don't liked them, because it was boring. I needed something for manage running processes in a background on my server, something what runs a crashed process again.

## Using

You have to edit `App.toml` file, for example:

```toml
[Startup]
	paths = [
		'c:\PlutonX\Server\PlutonCoreApp.exe',
		'c:\PlutonX\AgencyDB\Server\AgencyDB.exe'
	]
```
  
And after you need to start `StayResident.exe`
