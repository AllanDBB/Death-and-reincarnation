## Project Structure

The project follows a well-organized structure with source files separated into headers and implementation files:

```
Death-and-reincarnation/
├── main.cpp             # Application entry point
├── mainwindow.cpp       # Main GUI implementation
├── mainwindow.h         # Main window declarations
├── mainwindow.ui        # Qt UI file
├── src/                 # Source directory
│   ├── cpp/             # Implementation files
│   │   ├── angel.cpp    # Angel entity implementation
│   │   ├── graveyard.cpp # Graveyard system implementation
│   │   ├── heaven.cpp   # Heaven system implementation
│   │   ├── humanity.cpp # Humanity system implementation
│   │   ├── person.cpp   # Person entity implementation
│   │   └── world.cpp    # World system implementation
│   ├── headers/         # Header files
│   │   ├── angel.h      # Angel entity declarations
│   │   ├── graveyard.h  # Graveyard system declarations
│   │   ├── heaven.h     # Heaven system declarations
│   │   ├── humanity.h   # Humanity system declarations
│   │   ├── person.h     # Person entity declarations
│   │   └── world.h      # World system declarations
│   ├── names            # Data file for names
│   ├── lastNames        # Data file for last names
│   ├── religion         # Data file for religious beliefs
│   ├── countries        # Data file for countries
│   ├── majors           # Data file for professions/majors
│   ├── deathLog         # Log file for deaths
│   └── humanity         # Log file for humanity
└── build/               # Build output directory
```

## Core Components

### Person

The `Person` class represents individual entities with the following properties:

```cpp
struct Person {
    int id;
    QString firstName;
    QString lastName;
    QString country;
    QString belief;
    QString profession;
    QString birthDate;
    QString timeOfDeath;
    QString typeOfDeath;
    int sins[7]; // Seven deadly sins counter
    QVector<Person*> myFriends;
    QVector<Person*> reincarnations;
    bool condition; // Alive or dead
    
    // Linked list pointers for data structure management
    Person* leftPerson;
    Person* rightPerson;
    
    // Methods
    Person(int, QString, QString, QString, QString, QString, QString);
    QString toString();
    int getSinSum();
};
```

### Humanity

The `Humanity` class manages all living persons in the simulation:

```cpp
struct Humanity {
    Person* firstPerson;
    Person* lastPerson;
    int length;
    int deaths;
    
    // Methods for managing people
    void add(Person*, Person*, bool);
    Person* remove(int, Person*, bool);
    Person* find(int, Person*, bool);
    Person* createPerson(int, int, int, int, int);
    Person* resurrect(Person*);
    
    // Methods for behavior
    void humansSin();
    void makeFriends();
    
    // Utility methods
    QVector<Person*> sort(SinType);
    void showHeap(SinType);
    QVector<QString> getTopSinCountries(int);
    
    // Death methods
    QVector<Person*> killByHeap(int, SinType);
    QVector<Person*> killRandom(int);
    Person* killSpecific(int);
    
    // Logging methods
    void restoreLog_();
};
```

### Graveyard

The `Graveyard` class manages all deceased persons:

```cpp
struct Graveyard {
    Person* firstPerson;
    Person* lastPerson;
    int length;
    Humanity* humanity;
    
    // Methods
    void add(Person*);
    Person* remove(int);
    Person* find(int);
    QVector<Person*> sort(SinType);
    void restoreLog();
};
```

### Heaven

The `Heaven` class handles the reincarnation system:

```cpp
struct Heaven {
    // Methods
    QString reincarnatePerson();
    void generateLevel();
};
```

### Angel

The `Angel` class represents spiritual entities that guide reincarnated souls:

```cpp
struct Angel {
    QString name;
    int version;
    int generation;
    Person* saved;
    
    // Tree structure pointers
    Angel* firstChild;
    Angel* secondChild;
    Angel* thirdChild;
    
    Angel(QString, int, int, Person*);
};
```

### World

The `World` class represents the interaction between living and dead:

```cpp
struct World {
    Humanity* humanity;
    Graveyard* graveyard;
    int length;
    
    // Methods
    void add(Person*);
    void remove(int);
};
```

## User Interface

The main window interface is implemented in mainwindow.cpp and provides:

- Controls for creating new person entities
- Display of human attributes (name, country, belief, profession, etc.)
- Death controls with different killing methods:
  - Random probability death
  - Death by sin level (heap-based)
  - Specific ID death
- Reincarnation system visualization
- Sin statistics and tracking

## Key Features

1. **Person Creation**: Generate people with random attributes from data files
2. **Sin System**: Track seven deadly sins for each person
3. **Death System**: Multiple methods to remove people from the world
4. **Reincarnation**: Deceased people can be reincarnated with new attributes
5. **Friend Network**: People can establish friendships
6. **Logging**: Death and humanity logs track all events
7. **Statistics**: Track and display sin statistics by country

## Build System

The project uses CMake for building. You can find the build configurations in different directories under `build/` for various platforms:

- Desktop builds with MinGW (64-bit)
- Raspberry Pi 4 (64-bit) for embedded deployment

## Usage

1. Create individuals by specifying parameters
2. Allow them to accumulate sins
3. Kill individuals using different methods
4. Generate reincarnation levels for the deceased
5. View statistics and logs

## Data Flow

1. People are created and added to the `Humanity` system
2. People accumulate sins during their lifetime
3. When killed, they move from `Humanity` to the `Graveyard`
4. `Heaven` manages reincarnation, creating new `Person` entities
5. Angels guide souls through reincarnation cycles

## Implementation Details

The project uses a doubly-linked list structure for managing people in both `Humanity` and `Graveyard` classes, enabling efficient traversal and operations. Additionally, the sin system uses a heap-based approach for sorting and removing people based on their accumulated sins.