<h1>COMP 3004 - Team Project</h1>
<p>Submission for the winter 2024 Object Oriented Software Engineering Final Project.</p>

<h2>Neureset - Direct Neurofeedback EEG Device</h2>
<p>Simulation of the consumer EEG direct neurofeedback device called Neureset based on the LENS Neurofeedback system.</p>

<h2>Team Members:</h2>
<ul>
    <li>Adam Esanhaji: &nbsp;&nbsp;&nbsp;&nbsp; adamesanhaji@cmail.carleton.ca</li>
    <li>Anas Ismaili: &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; anasismaili@cmail.carleton.ca</li>
    <li>Joshua Mukasa: &nbsp;&nbsp;&nbsp;&nbsp; joshuamukasa@cmail.carleton.ca</li>
    <li>Kunal Barua: &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;kunalbarua@cmail.carleton.ca</li>
</ul>

<h2>Project Structure</h2>
<ul>
    <li>C++ Implementation is locating in the src folder</li>
    <li>Uses Cases are located in the report pdf</li>
    <li>UML Class diagram is located in the diagrams folder</li>
    <li>Sequence diagrams are located in the diagrams/Sequence folder</li>
    <li>State diagrams are located in the diagrams/State folder</li>
    <li>Design documentation is in the report pdf</li>
    <li>Traceability matrix is in the report pdf</li>
</ul>

<h2>Running Instructions</h2>
<ul>
    <li>Open the Neureset.pro file located in the src directory using Qt Creator</li>
    <li>Build the project and then run the project</li>
</ul>

<h2>Testing Video</h2>
<p>https://www.youtube.com/watch?v=UsAmreMHwq8</p>

<h2>Contributions:</h2>

Adam Esanhaji
<ul>
    <li>Worked on Use Cases and requirements with team</li>
    <li>Worked on UML Class Diagram with team</li>
    <li>Worked on sequence diagrams with team</li>
    <li>Wrote design explanations about strategy, mediator, and observer design patterns</li>
    <li>Created the MainWindow</li>
    <li>Created and designed the Neureset UI</li>
    <li>Implemented start, stop, and pause button handlers</li>
    <li>Implemented multithreading</li>
    <li>Implemented timer functionality</li>
    <li>Implemented pausing functionality using mutex</li>
    <li>Refactored the waveform generation class with Joshua</li>
    <li>Merged PC functionality to mainwindow with Kunal</li>
    <li>Worked on creating and implementing the main flow of the treatment process</li>
</ul>

Anas Ismaili
<ul>
    <li>Worked on Use Cases and requirements with team</li>
    <li>Worked on UML Class Diagram with team</li>
    <li>Created headset class and implemented functionality</li>
    <li>Created probe/electrode class and implemented functionality</li>
    <li>Worked on creating and implementing the main flow of the treatment process</li>
    <li>Worked on the logging of treatment/device actions to the console (analysis rounds, etc.) </li>
    <li>Implemented the functionality of the signal lights</li>
    <li>Implemented error and text displays for the UI</li>
    <li>Implemented disconnection/loss of contact of the electrodes</li>
    <li>Implemented the progress bar's functionality</li>
    <li>Created on/off states for the neureset, and implemented the power button's functionality</li>
    <li>Added timer to main screen during treatments, and implemented timer's functionality</li>
    <li>Worked on implementing pausing treatment functionality</li>
</ul>

Joshua Mukasa
<ul>
    <li>Worked on creating the main flow of the treatment process</li>
    <li>Created FileManager and implemented functionality</li>
    <li>Created SessionManager and implemented functionality</li>
    <li>Implemented battery functionality</li>
    <li>Created WaveformGenerator and implemented base funcionality</lie>
    <li>Implemented wave band changding through menubar</li>
    <li>Implemented battery recharging through menubar</li>
    <li>Implemented menu actions for headset connect/disconnect</li>
    <li>Added progress bar to UI</li>
    <li>General bug fixes</li>
    <li> Created state diagrams</li>
    <li>Updated UML class diagram</li>
    <li>Worked on Use Cases and requirements with team</li>
    <li>Worked on Requirements Matrix with team</li>
</ul>

Kunal Barua
<ul>
    <li>Created Sinewave class which produces the visualization for EEG waveforms</li>
    <li>Implemented the functionality for PC session log view displaying the EEG waveforms for a particular session when selected from PC ui</li>
    <li>Created PC class which displays the session log information in greater detail</li>
    <li>Added functionality for PC button which opens up a new window with PC ui and session log details.</li>
    <li>Implemented the functionality for Menu in collaboartion with my teammates, which takes appropriate action based on which menu item is selected</li>
    <li>Implemented functionality for menu button which takes back the Neureset device to main menu.</li>
    <li>Worked on Use Cases and requirements with team</li>
    <li>Contributed to UML case diagram in collabotation with the team </li>
    <li>Worked on creating and implementing the main flow of the treatment process</li>   
</ul>
