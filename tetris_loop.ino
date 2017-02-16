/*
 * This program uses a class to cause the piezo speaker to play melodies.  It sends
 * a square wave of the appropriate frequency to the piezo, generating
 * the corresponding tone.  The functions in the Song class are based off of the
 * Melody function downloaded from the Arduino website.
 * 
 * Last modified: November 13, 2013
 * Author: Michael Mackliet, mackliet
 *
 */
 
const int LENGTH = 45;
class Song{
  private:
    char notes[LENGTH];
    int beats[LENGTH];
    int tempo;
    int speakerPin;


/*This function plays a musical note.  It accepts a character which represents a certain
 * note and an int that represents the amount of time the note should be played.  The
 * following is a list of available notes to be played.  Characters to play the notes are 
 * equivalent to the name in the note column unless there is a character in parentheses to
 * the side.
 * 
 * 
 *  * note   frequency   period  timeHigh
 * g ($)      196 Hz    5102  2551
 * c          261 Hz    3830  1915  
 * csharp (%) 277 Hz    3610  1805
 * d          294 Hz    3400  1700  
 * e          329 Hz    3038  1519  
 * f          349 Hz    2864  1432  
 * gflat (&)  370 Hz    2703  1351
 * g          392 Hz    2550  1275  
 * a          440 Hz    2272  1136  
 * bflat (*)  466 Hz    2146  1073
 * b          493 Hz    2028  1014  
 * C          523 Hz    1912  956
 * Csharp (^) 554 Hz    1805  903
 * D          587 Hz    1704  852
 * E          659 Hz    1517  759
 * F          699 Hz    1431  715
 * G          784 Hz    1276  638
 * A          880 Hz    1136  568
 * 
 * Parameters:
 * char note:  the note to be played
 * int duration: the length of time to play the note
 * 
 * Returns
 * void 
 */
    void playNote(char note, int duration);

 /* This function plays a tone of a certain frequency given an int representing the half  
  *  the period of the waveform.  
  *  
  *The calculation of the tones is made following the mathematical
  * operation:
  *
  *       tone = period / 2 = 1 / (2 * toneFrequency) 
  * 
  * Parameters:
  * int tone:  half the period of the waveform
  * int duration: how long the tone should be played.
  *    
  */
    void playTone(int tone, int duration);

    
  public:
  /*
   * The constructor for the Song class.  A Song object is created from an array of 
   * characters representing notes, an array of ints representing the number of beats
   * each note is played for, an int representing the tempo, and an int representing which
   * digital pin should send out the output to make the piezo electric buzzer sound.
   * 
   * Parameters
   * char _notes[]--the notes to be played
   * int beats[]--how many beats each note should be played for
   * int _tempo--how fast or slow to play the Song (larger number will make it slower)
   * int speakerPin--the pin that will output the Song to the buzzer
   * 
   * Returns
   * void
   */
    Song(char _notes[], int beats[], int _tempo,int speakerPin);
  /*This function plays a song using a Song object.
   *
   *Parameters:
   *none
   *
   *Returns:
   *none
   */
    void playSong();
};

Song::Song(char _notes[], int _beats[], int _tempo, int _speakerPin){
  speakerPin = _speakerPin;
  pinMode(speakerPin, OUTPUT);
  tempo = _tempo;
  for(int i=0;i<LENGTH;i++){
    notes[i] = _notes[i];
    beats[i] = _beats[i];
  }
}

void Song::playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

void Song::playNote(char note, int duration) {
  char names[] = {'$', 'c', '%', 'd', 'e', 'f', '&', 'g', 'a','*', 'b', 'C', '^', 'D', 'E', 'F', 'G', 'A' };
  int tones[] = {2551, 1915, 1805, 1700, 1519, 1432, 1351, 1275, 1136, 1073, 1014, 956, 903, 852, 759, 715, 638, 568};
  
  // play the tone corresponding to the note name
  for (int i = 0; i < 18; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}

void Song::playSong(){
  for (int i = 0; i < LENGTH; i++) {
    if (notes[i] == ' ') {
      delay(beats[i] * tempo); // rest
    } else {
      playNote(notes[i], beats[i] * tempo);
    }
    
    // pause between notes
  }
}


char notes_tetrisPart1 [LENGTH] = {'a', 'e', 'f', 'g', 'a', 'g', 'f', 'e', 'd', 'd', 'f', 'a', 'g', 'f', 'e', 'f', 'g', 'a', 'f', 'd', 'd', ' ', 'g', '*', 'D', 'C', '*', 'a', 'f', 'a', 'g', 'f', 'e', 'e', 'f', 'g', 'a', 'f', 'd', 'd', ' '};
int beats_tetrisPart1 [LENGTH] = {4, 2, 2, 2, 1, 1, 2, 2, 4, 2, 2, 4, 2, 2, 6, 2, 4, 4, 4, 4, 8, 1, 4, 2, 4, 2, 2, 6, 2, 4, 2, 2, 4, 2, 2, 4, 4, 4, 4, 4, 4};
char notes_tetrisPart2 [LENGTH] = {'a', 'f', 'g', 'e', 'f', 'd', '%', 'e', ' ', 'a', 'f', 'g', 'e', 'f', 'a', 'D', '^', ' '};
int beats_tetrisPart2 [LENGTH] = {8, 8, 8, 8, 8, 8, 8, 4, 4, 8, 8, 8, 8, 4, 4, 8, 8, 8};


Song tetrisPart1(notes_tetrisPart1, beats_tetrisPart1, 100, 9);
Song tetrisPart2(notes_tetrisPart2, beats_tetrisPart2, 100, 9);


void setup() {
  Serial.begin(9600);
}


void loop() {
    tetrisPart1.playSong();
    tetrisPart1.playSong();
    tetrisPart2.playSong();
    tetrisPart1.playSong();
    tetrisPart1.playSong();
  }


