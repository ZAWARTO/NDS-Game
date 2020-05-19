// This procedure initializes the interrupt table so that the interrupt manager knows
// what attention routine you have to execute when an interruption request arrives. It is also
// here where the peripheral control registers are configured.

extern void interrupciones();

extern void HabilitarInterrupciones();
extern void ProgramarRegistrosControl();
extern void DefinirVectorInterrupciones();
extern void InhibirInterrupciones();
