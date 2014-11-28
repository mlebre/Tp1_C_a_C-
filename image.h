class image
{
  private:
//=============================================================
//                        Parameters of picture  	
//=============================================================  	
  	int height;
  	int width;
  	unsigned char * pix;

  public:
//=============================================================
//                        Constructors 	
//=============================================================  

    image(void);
    image(const image& model);

//=============================================================
//                        Destructors  
//=============================================================  
   ~image(void);
//=============================================================
//                        Getters 	
//=============================================================  
    int Get_height(void) const;
    int Get_width(void) const;
    unsigned char * Get_pix(void) const;

//=============================================================
//                        Methods 	
//=============================================================  
  	void ppm_read_from_file(const char * title);
  	void ppm_desaturate(void);
  	void ppm_write_to_file(const char *title);
  	void ppm_shrink(const int factor);


};