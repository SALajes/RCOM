#include "state_machine.h"

void advance_state_UA(char byte, states* state) {
  if (*state == START) {
    if (byte == FLAG_RCV) {
      *state = FLAG_OK;
    }
  } else if (*state == FLAG_OK) {
    if (byte == FLAG_RCV) {
    }  // mantem se
    else if (byte == A_RCV) {
      *state = A_OK;
    } else {
      *state = START;
    }
  } else if (*state == A_OK) {
    if (byte == C_RCV) {
      *state = C_OK;
    } else if (byte == FLAG_RCV) {
      *state = FLAG_OK;
    } else {
      *state = START;
    }
  } else if (*state == C_OK) {
    if (byte == BCC_RCV) {
      *state = BCC_OK;
    } else if (byte == FLAG_RCV) {
      *state = FLAG_OK;
    } else {
      *state = START;
    }
  } else if (*state == BCC_OK) {
    if (byte == FLAG_RCV) {
      *state = STOP;
    } else {
      *state = START;
    }
  } else if (*state == STOP) {
  }
}

void advance_state_SET(char byte, states* state) {
  if (*state == START) {
    if (byte == FLAG_RCV) {
      *state = FLAG_OK;
    }
  } else if (*state == FLAG_OK) {
    if (byte == FLAG_RCV) {
    } else if (byte == A_SND) {
      *state = A_OK;
    } else {
      *state = START;
    }
  } else if (*state == A_OK) {
    if (byte == C_SND) {
      *state = C_OK;
    } else if (byte == FLAG_RCV) {
      *state = FLAG_OK;
    } else {
      *state = START;
    }
  } else if (*state == C_OK) {
    if (byte == BCC_SND) {
      *state = BCC_OK;
    } else if (byte== FLAG_RCV) {
      *state = FLAG_OK;
    } else {
      *state = START;
    }
  } else if (*state == BCC_OK) {
    if (byte == FLAG_RCV) {
      *state = STOP;
    } else {
      *state = START;
    }
  } else if (*state == STOP) {
  }
}

void advance_state_I(char byte, states* state) {
  if (*state == START) {
    if (byte == FLAG_RCV) {
      *state = FLAG_OK;
    }
  } else if (*state == FLAG_OK) {
    if(byte == FLAG_RCV) return;
    if (byte == A_SND) {
      *state = A_OK;
    } else {
      *state = START;
    }
  } else if (*state == A_OK) {
    if (byte == C_I0 || byte == C_I1) {
      *state = C_OK;
    } else if (byte == FLAG_RCV) {
      *state = FLAG_OK;
    } else {
      *state = START;
    }
  } else if (*state == C_OK) {
    if (byte == (A_SND ^ C_I0) || byte == (A_SND ^ C_I1)) {
      *state = BCC_OK;
    } else if (byte == FLAG_RCV) {
      *state = FLAG_OK;
    } else {
      *state = START;
    }
  } else if (*state == BCC_OK) {
    if (byte == FLAG_RCV) {
      *state = START;
    } else
      *state = DATA_R;
  } else if (*state == DATA_R) {
    if (byte == FLAG_RCV) {
      *state = STOP;
    } else
      *state = DATA_R;
  } else if (*state == STOP) {
  }
}

void advance_state_RR(unsigned char byte, states* state) {

  if (*state == START) {
    if (byte == FLAG_RCV) {
      *state = FLAG_OK;
    }
  } else if (*state == FLAG_OK) {
    if (byte == FLAG_RCV) {
    } else if (byte == A_RCV) {
      *state = A_OK;
    } else {
      *state = START;
    }
  } else if (*state == A_OK) {
    if (byte == C_RR0 || byte == C_RR1 || byte == C_REJ0 || byte == C_REJ1) {
      *state = C_OK;
    } else if (byte == FLAG_RCV) {
      *state = FLAG_OK;
    } else {
      *state = START;
    }
  } else if (*state == C_OK) {
    if (byte == (A_RCV ^ C_RR0) || byte == ( A_RCV ^ C_RR1) ||
        byte == (A_RCV ^ C_REJ0) || byte == (A_RCV ^ C_REJ1)) {
      *state = BCC_OK;
    } else if (*state == FLAG_RCV) {
      *state = FLAG_OK;
    } else {
      *state = START;
    }
  } else if (*state == BCC_OK) {
    if (byte == FLAG_RCV) {
      *state = STOP;
    } else {
      *state = START;
    }
  } else if (*state == STOP) {
  }
}
