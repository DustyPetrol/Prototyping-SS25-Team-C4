# Prototyping SS25 Group C4

## Distribution of tasks

| №     | Task                  | Short summary                                                                                                           | Responsible person | Deadline       |        Status         |
|:------|:----------------------|:------------------------------------------------------------------------------------------------------------------------|:-------------------|:---------------|:---------------------:|
| **1** | 3D-modelling          | Model and submit parts for 3D-printing: <br/> - motor holders<br/> - IR-sensor holders<br/> - battery/breadboard holder | Oleg Kelner        | 24.04.25 00:00 |   *Done (20.04.25)*   |
| **2** | Requirements Diagram  | Create Requirements Diagram for the prototype                                                                           | Petr Lavrenov      | 27.04.25       | *Done, to be refined* |
| **3** | Use Case Diagram      | Create Use Case Diagram for the prototype                                                                               | Turja Barua        | 27.04.25       |     *In process*      |
| **4** | Structure             | Create Structure for the prototype                                                                                      | Petr Lavrenov      | 27.04.25       |     *In process*      |
| **5** | State Machine Diagram | Create State Machine Diagram for the prototype                                                                          | Petr Lavrenov      | 27.04.25       |     *In process*      |
| **6** | Tinkercad Simulation  | Create Tinkercad simulation of the prototype                                                                            | Turja Barua        | 27.04.25       |     *In process*      |
| **7** | Assembling            | Assemble the prototype: <br/> - fix 3D-printed parts on the chassis<br/> - solder power wires<br/> - connect everything | Oleg Kelner        | 05.05.25       |     *In process*      |
| **8** | 3D-modelling          | Model and submit parts for 3D-printing: <br/> - ultrasonic holder<br/> - RGB-sensor holder                              | Oleg Kelner        | 05.05.25       |     *Not started*     |
| **9** | Programming           | *to be refined*                                                                                                         | Oleg Kelner        | 05.05.25       |     *Not started*     |

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
