# Prototyping SS25 Group C4

## Distribution of tasks

| №     | Task                 | Short summary                                                                                                           | Responsible person | Deadline       |    Status     |
|:------|:---------------------|:------------------------------------------------------------------------------------------------------------------------|:-------------------|:---------------|:-------------:|
| **1** | 3D-modelling         | Model and submit parts for 3D-printing: <br/> - motor holders<br/> - IR-sensor holders<br/> - battery/breadboard holder | Oleg Kelner        | 24.04.25 00:00 | *In process*  |
| **2** | Requirements Diagram | Create Requirements Diagram for the prototype                                                                           | Petr Lavrenov      | 27.04.25       | *In process*  |
| **3** | Use Case Diagram     | Create Use Case Diagram for the prototype                                                                               | Turja Barua        | 27.04.25       | *Not started* |

## Project structure

### Documentation

```
Documentation/
|— Lectures/
|— Papyrus/
|— Assembly.png
```

`Lectures` contain lectures and other materials given by professors.

`Papyrus` contain **Papyrus** project with *SysML* diagrams.

`Assembly.png` - picture of the assembled prototype in 3D-modelling software.

### 3D models

```
3D models/
|— Basic components/
|— Assembly.iam 
```

`Basic components` contain 3D models of given components, such as Arduino Uno, battery, motors etc.

`Assembly.iam` - an assembly of the prototype made in **Autodesk Inventor**.

### Software
```
Software/
|— src/src.ino
```

`src/src.ino` - Arduino IDE main file.
