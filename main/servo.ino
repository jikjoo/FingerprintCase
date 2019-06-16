void closeServo(){
    for(pos ; pos < max_pos ; pos += 1){
        servo1.write(pos);
        //servo2.write(pos);
      } 
    isOpen = false;
}

void openServo(){
    for(pos ; pos > initial_pos ; pos -= 1){
        servo1.write(pos);
      } 
    isOpen = true;
}
