VFSreunpack::filesXBB(FileBuffer file)
{
  //some old removed code

  //looping through each file data to find and pull the names
  for (int i= 0; i < fileCount; i++)
  {
    //get start pointer
    uint8_t* sbuffer= reader.read(4);
    uint32_t startPTR= sbuffer[0] | (sbuffer[1] << 8) | (sbuffer[2] << 16) | (sbuffer[3] << 24);
    debug("[VFSreunpack::filesXBB] start ptr construct: "+i2h(sbuffer[0])+" "+i2h(sbuffer[1])+" "+i2h(sbuffer[2])+" "+i2h(sbuffer[3]));
    debug("[VFSreunpack::filesXBB] start ptr at: "+l2h(startPTR)+" => "+std::to_string(startPTR));
    //get end pointer
    uint8_t* ebuffer= reader.read(4);
    uint32_t endPTR= ebuffer[0] | (ebuffer[1] << 8) | (ebuffer[2] << 16) | (ebuffer[3] << 24);
    debug("[VFSreunpack::filesXBB] end ptr construct: "+i2h(ebuffer[0])+" "+i2h(ebuffer[1])+" "+i2h(ebuffer[2])+" "+i2h(ebuffer[3]));
    debug("[VFSreunpack::filesXBB] end ptr at: "+l2h(endPTR)+" => "+std::to_string(endPTR));

    //get filename pointer
    uint8_t* fbuffer= reader.read(4);
    uint32_t fnamePTR= fbuffer[0] | (fbuffer[1] << 8) | (fbuffer[2] << 16) | (fbuffer[3] << 24);
    debug("[VFSreunpack::filesXBB] filename ptr construct: "+i2h(fbuffer[0])+" "+i2h(fbuffer[1])+" "+i2h(fbuffer[2])+" "+i2h(fbuffer[3]));
    debug("[VFSreunpack::filesXBB] filename ptr at: "+l2h(fnamePTR)+" => "+std::to_string(fnamePTR));
  }

  //ignore metablob (fileCount * 8)
  reader.i(fileCount * 8);

  //get filename for each file in data
  for (int i= 0; i < fileCount; i++)
  //ah shit.. here we go again...
  {
    std::vector<uint8_t> dirtyFileName;

    while (true)
    {
      uint8_t rb= reader.read();
      if (rb == 0x00) {break;}
      debug("[VFSreunpack::filesXBB] pushing character ["+i2h(rb)+"] to filename vector");
      dirtyFileName.push_back(rb);
    }

    uint8_t* slightlyLessDirtyFileName= new uint8_t[dirtyFileName.size()];
    for (size_t i= 0; i < dirtyFileName.size(); i++)
    {
      slightlyLessDirtyFileName[i]= dirtyFileName[i];
    }

    std::string filename= uc2s(slightlyLessDirtyFileName);
    debug("[VFSreunpack::filesXBB] filename delivered: "+filename);
  }


