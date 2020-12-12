class Color
{
private:
	unsigned short Alpha;
	unsigned short Red;
	unsigned short Green;
	unsigned short Blue;
	
public:
	Color(){};
	Color(unsigned short r, unsigned short g, unsigned short b);
	Color(unsigned short a, unsigned short r, unsigned short g, unsigned short b);
	Color(unsigned int hex_argb);
	
	void Set_RGB(unsigned short r, unsigned short g, unsigned short b);
	void Set_RGB(unsigned int hex_rgb);
	void Set_ARGB(unsigned short a, unsigned short r, unsigned short g, unsigned short b);
	void Set_ARGB(unsigned int hex_argb);
	
	unsigned short Get_Alpha_Int(){ return Alpha; };
	unsigned short Get_Red_Int()  { return Red; };
	unsigned short Get_Green_Int(){ return Green; };
	unsigned short Get_Blue_Int() { return Blue; };
	unsigned int   Get_RGB_Int();
	unsigned int   Get_ARGB_Int();
	unsigned short Get_Grey_Scale();
};