


struct GameComponent {
  typedef enum {
      ShieldController    = 'S',
      ReactorCore         = 'R',
      WiringPanel         = 'W',
      KeyPad              = 'K',
      CommunicationsArray = 'C',
  } Type;
};



// ********** ShieldController *************
struct ShieldControllerMethod {
  typedef enum {
    getter = 'G',
    setter = 'S',
  } Type;
};

struct ShieldControllerProperty {
  typedef enum {
    isActive = 'A',
  } Type;
};

struct ShieldControllerEvent {
  typedef enum {
    TaskStarted = 'S',
    TaskCompleted = 'C',
    ButtonActivated = 'A',
    ButtonDeactivated = 'D',
  } Type;
};

struct ShieldControllerState {
  typedef enum {
    idle = 'H',
     = 'T',
  } Type;
};
