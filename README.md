## Midi To Micro

#### Steps:
1. Acquire a .mid file.
2. Download the free version of Synthfont http://www.synthfont.com/Downloads.html.
3. Make sure that only one note is played at a time.
4. Go to the "3 Midi events" tab.
5. Find "Show these events" and select "Note on & off".
6. Click "Save as text" and save it as midievents.txt in the same folder as miditest.exe.
7. Run miditest.exe  from the "ON PC" folder.
8. Copy and paste the arrays and notecount into ExampleProgram1.c or PlayTune.ino and compile the project.


#### Troubleshooting
- If miditest.exe doesn't work, try recompiling miditest.c
- If the tune is too fast or too slow, try changing the PPQ on line 10.
