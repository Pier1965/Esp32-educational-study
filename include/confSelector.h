// Modo di funzionamento 0 : clock - 1 : radioclockwatch
int WMode = 0;
int oldWMode = 0;

void confSelector(){
    pinMode(RCSelector, INPUT);
}

int workingMode(){
    return digitalRead(RCSelector);
}
