class image
{
  private:
  	int height;
  	int width;
  	unsigned char * pix;

  public:
    image(void);
    image(const image& model);
    

    int Get_height(void) const;
    int Get_width(void) const;
    unsigned char * Get_pix(void) const;

    void Set_name(void);

  	void ppm_read_from_file(const char * title);
  	void ppm_desaturate(void);
  	void ppm_write_to_file(const char *title);
  	void ppm_shrink(const int factor);


};