class image
{
  private:
  	int height;
  	int width;
  	unsigned char * pix;

  public:
    image(void);
    int Get_height(void) const;
    int Get_width(void) const;

    void Set_name(void);

  	void ppm_read_from_file(const char * title);


};