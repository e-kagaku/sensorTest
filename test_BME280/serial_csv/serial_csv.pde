import processing.serial.*;
PrintWriter output;
Serial myPort;
boolean flg_start = false;
String str_format = "time, BME280, TMP36GZ, DHT11";
String datastr;
String port = "/dev/cu.usbmodem143220";

void setup()
{
  //println(Serial.list());  // 使えるポート一覧
  myPort = new Serial(this, port, 9600);
  //myPort = new Serial(this, Serial.list()[0], 9600); // myPortを最初のシリアルポート、9600bpsに設定
  myPort.clear();
}

void draw() {
  if ( myPort.available() > 0) {
    delay(100);
    datastr = myPort.readString();
    if (datastr != null) {
      if (flg_start) output.println(datastr);
    }
  }
}


void keyPressed() {
  if ( key == 's' ) {
    flg_start  = !flg_start;

    if ( flg_start == false ) {
      // end of recording
      println("End Recording");
      output.flush(); 
      output.close();
    } else if ( flg_start == true ) {
      // begining of recording
      println("Begin Recording");
      output = createWriter( "data.csv"); 
      output.println( str_format );
    }
  }
}
