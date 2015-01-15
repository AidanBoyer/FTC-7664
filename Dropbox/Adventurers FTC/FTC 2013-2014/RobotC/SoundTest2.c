void HarkTheHerald()
{
  //        140 = Tempo
  //          6 = Default octave
  //    Quarter = Default note length
  //        10% = Break between notes
  //
  PlayTone(  784,   39); wait1Msec( 429);  // Note(C)
  PlayTone( 1047,   39); wait1Msec( 429);  // Note(F)
  PlayTone( 1047,   77); wait1Msec( 857);  // Note(F, Duration(Half))
  PlayTone(  988,   19); wait1Msec( 214);  // Note(E, Duration(Eighth))
  PlayTone( 1047,   39); wait1Msec( 429);  // Note(F)
  PlayTone( 1320,   39); wait1Msec( 429);  // Note(A)
  PlayTone( 1320,   39); wait1Msec( 429);  // Note(A)
  PlayTone( 1175,   39); wait1Msec( 429);  // Note(G)
  PlayTone( 1481,   39); wait1Msec( 429);  // Note(B)
  PlayTone( 1481,   39); wait1Msec( 429);  // Note(B)
  PlayTone( 1481,   39); wait1Msec( 429);  // Note(B)
  return;
}


task main()
{
HarkTheHerald();


}
