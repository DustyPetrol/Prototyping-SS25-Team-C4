# Prototyping SS25 Group C4

## Distribution of tasks

| №      | Task                  | Short summary                                                                                                           | Responsible person | Deadline |        Status         |
|:-------|:----------------------|:------------------------------------------------------------------------------------------------------------------------|:-------------------|:---------|:---------------------:|
| **1**  | 3D-modelling          | Model and submit parts for 3D-printing: <br/> - motor holders<br/> - IR-sensor holders<br/> - battery/breadboard holder | Oleg Kelner        | 24.04.25 |        *Done*         |
| **2**  | Requirements Diagram  | Create Requirements Diagram for the prototype                                                                           | Petr Lavrenov      | 27.04.25 | *Done, to be refined* |
| **3**  | Use Case Diagram      | Create Use Case Diagram for the prototype                                                                               | Petr Lavrenov      | 04.05.25 |     *In process*      |
| **4**  | Structure Diagram     | Create Structure diagram for the prototype                                                                              | Petr Lavrenov      | 04.05.25 |        *Done*         |
| **5**  | State Machine Diagram | Create State Machine Diagram for the prototype                                                                          | Petr Lavrenov      | 04.05.25 |     *In process*      |
| **6**  | Tinkercad Simulation  | Create Tinkercad simulation of the prototype                                                                            | Oleg Kelner        | 04.05.25 |        *Done*         |
| **7**  | Assembling            | Assemble the prototype: <br/> - fix 3D-printed parts on the chassis<br/> - solder power wires<br/> - connect everything | Oleg Kelner        | 10.05.25 |     *In process*      |
| **8**  | 3D-modelling          | Model and submit parts for 3D-printing: <br/> - ultrasonic holder<br/> - RGB-sensor holder                              | Oleg Kelner        | 05.05.25 |     *Not started*     |
| **9**  | Programming           | *to be refined*                                                                                                         | Oleg Kelner        | 15.05.25 |     *Not started*     |
| **10** | Sequence Diagram      | Create Sequence Diagram for the prototype                                                                               | Turja Barua        | 04.05.25 |     *Not started*     |

## Project structure

### Documentation

```
Documentation/
|— Lectures/
|— Papyrus/
|— TinkerCad/
|— Assembly.png
```

`Lectures` contain lectures and other materials given by professors.

`Papyrus` contain **Papyrus** project with *SysML* diagrams.

`TinkerCad` contain **TinkerCad** simulation files (pic of the circuit and code).

`Assembly.png` - picture of the assembled prototype in 3D-modelling software.

### 3D models

```
3D models/
|— Basic components/
|— Details to print/
|— Assembly.iam 
```

`Basic components` contain 3D models of given components, such as Arduino Uno, battery, motors etc.

`Details to print` contain 3D-modeled parts for the printing (motor holder, IR-sensor holder etc.).

`Assembly.iam` - an assembly of the prototype made in **Autodesk Inventor**.

### Software

```
Software/
|— src/src.ino
```

`src/src.ino` - Arduino IDE main file.
