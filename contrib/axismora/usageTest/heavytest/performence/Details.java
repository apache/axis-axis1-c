package heavytest.performence;
/**
 * <p>This class is genarated by the tool WSDL2Ws.
 * It take care of the serialization and the desirialization of
 * the parameter types.
 * except for the serialize(), desirialize() methods it it a bean class.
 * We are specially concerned about the alogorithem used in the desirialize method.
 * If you have any suggestions to improve, your comments are welcome.</p>
 */ 
public class Details  implements org.apache.axismora.encoding.InOutParameter{
	private java.lang.String Url;
	private java.lang.String Asin;
	private java.lang.String ProductName;
	private java.lang.String Catalog;
	private heavytest.performence.KeyPhrase[] KeyPhrases;
	private java.lang.String[] Artists;
	private java.lang.String[] Authors;
	private java.lang.String Mpn;
	private java.lang.String[] Starring;
	private java.lang.String[] Directors;
	private java.lang.String TheatricalReleaseDate;
	private java.lang.String ReleaseDate;
	private java.lang.String Manufacturer;
	private java.lang.String Distributor;
	private java.lang.String ImageUrlSmall;
	private java.lang.String ImageUrlMedium;
	private java.lang.String ImageUrlLarge;
	private java.lang.String ListPrice;
	private java.lang.String OurPrice;
	private java.lang.String UsedPrice;
	private java.lang.String RefurbishedPrice;
	private java.lang.String CollectiblePrice;
	private java.lang.String ThirdPartyNewPrice;
	private java.lang.String NumberOfOfferings;
	private java.lang.String ThirdPartyNewCount;
	private java.lang.String UsedCount;
	private java.lang.String CollectibleCount;
	private java.lang.String RefurbishedCount;
	private heavytest.performence.ThirdPartyProductInfo ThirdPartyProductInfo;
	private java.lang.String SalesRank;
	private heavytest.performence.BrowseNode[] BrowseList;
	private java.lang.String Media;
	private java.lang.String ReadingLevel;
	private java.lang.String Publisher;
	private java.lang.String NumMedia;
	private java.lang.String Isbn;
	private java.lang.String[] Features;
	private java.lang.String MpaaRating;
	private java.lang.String EsrbRating;
	private java.lang.String AgeGroup;
	private java.lang.String Availability;
	private java.lang.String Upc;
	private heavytest.performence.Track[] Tracks;
	private java.lang.String[] Accessories;
	private java.lang.String[] Platforms;
	private java.lang.String Encoding;
	private heavytest.performence.Reviews Reviews;
	private java.lang.String[] SimilarProducts;
	private java.lang.String[] Lists;
	private java.lang.String Status;

	public Details(){
	}
	public Details(java.lang.String Url,java.lang.String Asin,java.lang.String ProductName,java.lang.String Catalog,heavytest.performence.KeyPhrase[] KeyPhrases,java.lang.String[] Artists,java.lang.String[] Authors,java.lang.String Mpn,java.lang.String[] Starring,java.lang.String[] Directors,java.lang.String TheatricalReleaseDate,java.lang.String ReleaseDate,java.lang.String Manufacturer,java.lang.String Distributor,java.lang.String ImageUrlSmall,java.lang.String ImageUrlMedium,java.lang.String ImageUrlLarge,java.lang.String ListPrice,java.lang.String OurPrice,java.lang.String UsedPrice,java.lang.String RefurbishedPrice,java.lang.String CollectiblePrice,java.lang.String ThirdPartyNewPrice,java.lang.String NumberOfOfferings,java.lang.String ThirdPartyNewCount,java.lang.String UsedCount,java.lang.String CollectibleCount,java.lang.String RefurbishedCount,heavytest.performence.ThirdPartyProductInfo ThirdPartyProductInfo,java.lang.String SalesRank,heavytest.performence.BrowseNode[] BrowseList,java.lang.String Media,java.lang.String ReadingLevel,java.lang.String Publisher,java.lang.String NumMedia,java.lang.String Isbn,java.lang.String[] Features,java.lang.String MpaaRating,java.lang.String EsrbRating,java.lang.String AgeGroup,java.lang.String Availability,java.lang.String Upc,heavytest.performence.Track[] Tracks,java.lang.String[] Accessories,java.lang.String[] Platforms,java.lang.String Encoding,heavytest.performence.Reviews Reviews,java.lang.String[] SimilarProducts,java.lang.String[] Lists,java.lang.String Status){
		this.Url = Url;
		this.Asin = Asin;
		this.ProductName = ProductName;
		this.Catalog = Catalog;
		this.KeyPhrases = KeyPhrases;
		this.Artists = Artists;
		this.Authors = Authors;
		this.Mpn = Mpn;
		this.Starring = Starring;
		this.Directors = Directors;
		this.TheatricalReleaseDate = TheatricalReleaseDate;
		this.ReleaseDate = ReleaseDate;
		this.Manufacturer = Manufacturer;
		this.Distributor = Distributor;
		this.ImageUrlSmall = ImageUrlSmall;
		this.ImageUrlMedium = ImageUrlMedium;
		this.ImageUrlLarge = ImageUrlLarge;
		this.ListPrice = ListPrice;
		this.OurPrice = OurPrice;
		this.UsedPrice = UsedPrice;
		this.RefurbishedPrice = RefurbishedPrice;
		this.CollectiblePrice = CollectiblePrice;
		this.ThirdPartyNewPrice = ThirdPartyNewPrice;
		this.NumberOfOfferings = NumberOfOfferings;
		this.ThirdPartyNewCount = ThirdPartyNewCount;
		this.UsedCount = UsedCount;
		this.CollectibleCount = CollectibleCount;
		this.RefurbishedCount = RefurbishedCount;
		this.ThirdPartyProductInfo = ThirdPartyProductInfo;
		this.SalesRank = SalesRank;
		this.BrowseList = BrowseList;
		this.Media = Media;
		this.ReadingLevel = ReadingLevel;
		this.Publisher = Publisher;
		this.NumMedia = NumMedia;
		this.Isbn = Isbn;
		this.Features = Features;
		this.MpaaRating = MpaaRating;
		this.EsrbRating = EsrbRating;
		this.AgeGroup = AgeGroup;
		this.Availability = Availability;
		this.Upc = Upc;
		this.Tracks = Tracks;
		this.Accessories = Accessories;
		this.Platforms = Platforms;
		this.Encoding = Encoding;
		this.Reviews = Reviews;
		this.SimilarProducts = SimilarProducts;
		this.Lists = Lists;
		this.Status = Status;
	}


	public org.apache.axismora.encoding.InParameter desierialize(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		int count = 50;
		if(org.apache.axismora.wsdl2ws.java.ParmWriter.tag == null)
			org.apache.axismora.wsdl2ws.java.ParmWriter.tag= msgdata.getTag();
		//come to first start tag
		while(!(org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getType() == org.xmlpull.v1.XmlPullParser.START_TAG))
			org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
		//skip it says the type
		org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
		//if the type of the next tag is end tag that means the content of element is null
		if(org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getType() == org.xmlpull.v1.XmlPullParser.END_TAG)			return null;

		for(int i = 0;i<count;i++) {
			while(!(org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getType() == org.xmlpull.v1.XmlPullParser.START_TAG))
				org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
				String localName = org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getLocalpart();
				if(localName.equalsIgnoreCase("Url")) {
					this.Url= new org.apache.axismora.wrappers.simpleType.StringParam(msgdata).getParam();
				}else if (localName.equalsIgnoreCase("Asin")) {
					this.Asin= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("ProductName")) {
					this.ProductName= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("Catalog")) {
					this.Catalog= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("KeyPhrases")) {
					heavytest.performence.ArrayOfKeyPhrase arrayT4 = (new heavytest.performence.ArrayOfKeyPhrase());
					arrayT4.desierialize(msgdata);
					this.KeyPhrases = arrayT4.getParam();
				}else if (localName.equalsIgnoreCase("Artists")) {
					heavytest.performence.ArrayOf_xsd_string arrayT5 = (new heavytest.performence.ArrayOf_xsd_string());
					arrayT5.desierialize(msgdata);
					this.Artists = arrayT5.getParam();
				}else if (localName.equalsIgnoreCase("Authors")) {
					heavytest.performence.ArrayOf_xsd_string arrayT6 = (new heavytest.performence.ArrayOf_xsd_string());
					arrayT6.desierialize(msgdata);
					this.Authors = arrayT6.getParam();
				}else if (localName.equalsIgnoreCase("Mpn")) {
					this.Mpn= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("Starring")) {
					heavytest.performence.ArrayOf_xsd_string arrayT8 = (new heavytest.performence.ArrayOf_xsd_string());
					arrayT8.desierialize(msgdata);
					this.Starring = arrayT8.getParam();
				}else if (localName.equalsIgnoreCase("Directors")) {
					heavytest.performence.ArrayOf_xsd_string arrayT9 = (new heavytest.performence.ArrayOf_xsd_string());
					arrayT9.desierialize(msgdata);
					this.Directors = arrayT9.getParam();
				}else if (localName.equalsIgnoreCase("TheatricalReleaseDate")) {
					this.TheatricalReleaseDate= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("ReleaseDate")) {
					this.ReleaseDate= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("Manufacturer")) {
					this.Manufacturer= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("Distributor")) {
					this.Distributor= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("ImageUrlSmall")) {
					this.ImageUrlSmall= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("ImageUrlMedium")) {
					this.ImageUrlMedium= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("ImageUrlLarge")) {
					this.ImageUrlLarge= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("ListPrice")) {
					this.ListPrice= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("OurPrice")) {
					this.OurPrice= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("UsedPrice")) {
					this.UsedPrice= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("RefurbishedPrice")) {
					this.RefurbishedPrice= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("CollectiblePrice")) {
					this.CollectiblePrice= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("ThirdPartyNewPrice")) {
					this.ThirdPartyNewPrice= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("NumberOfOfferings")) {
					this.NumberOfOfferings= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("ThirdPartyNewCount")) {
					this.ThirdPartyNewCount= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("UsedCount")) {
					this.UsedCount= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("CollectibleCount")) {
					this.CollectibleCount= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("RefurbishedCount")) {
					this.RefurbishedCount= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("ThirdPartyProductInfo")) {
					this.ThirdPartyProductInfo= (new heavytest.performence.ThirdPartyProductInfo());
					this.ThirdPartyProductInfo.desierialize(msgdata);
				}else if (localName.equalsIgnoreCase("SalesRank")) {
					this.SalesRank= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("BrowseList")) {
					heavytest.performence.ArrayOfBrowseNode arrayT30 = (new heavytest.performence.ArrayOfBrowseNode());
					arrayT30.desierialize(msgdata);
					this.BrowseList = arrayT30.getParam();
				}else if (localName.equalsIgnoreCase("Media")) {
					this.Media= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("ReadingLevel")) {
					this.ReadingLevel= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("Publisher")) {
					this.Publisher= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("NumMedia")) {
					this.NumMedia= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("Isbn")) {
					this.Isbn= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("Features")) {
					heavytest.performence.ArrayOf_xsd_string arrayT36 = (new heavytest.performence.ArrayOf_xsd_string());
					arrayT36.desierialize(msgdata);
					this.Features = arrayT36.getParam();
				}else if (localName.equalsIgnoreCase("MpaaRating")) {
					this.MpaaRating= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("EsrbRating")) {
					this.EsrbRating= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("AgeGroup")) {
					this.AgeGroup= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("Availability")) {
					this.Availability= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("Upc")) {
					this.Upc= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("Tracks")) {
					heavytest.performence.ArrayOfTrack arrayT42 = (new heavytest.performence.ArrayOfTrack());
					arrayT42.desierialize(msgdata);
					this.Tracks = arrayT42.getParam();
				}else if (localName.equalsIgnoreCase("Accessories")) {
					heavytest.performence.ArrayOf_xsd_string arrayT43 = (new heavytest.performence.ArrayOf_xsd_string());
					arrayT43.desierialize(msgdata);
					this.Accessories = arrayT43.getParam();
				}else if (localName.equalsIgnoreCase("Platforms")) {
					heavytest.performence.ArrayOf_xsd_string arrayT44 = (new heavytest.performence.ArrayOf_xsd_string());
					arrayT44.desierialize(msgdata);
					this.Platforms = arrayT44.getParam();
				}else if (localName.equalsIgnoreCase("Encoding")) {
					this.Encoding= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("Reviews")) {
					this.Reviews= (new heavytest.performence.Reviews());
					this.Reviews.desierialize(msgdata);
				}else if (localName.equalsIgnoreCase("SimilarProducts")) {
					heavytest.performence.ArrayOf_xsd_string arrayT47 = (new heavytest.performence.ArrayOf_xsd_string());
					arrayT47.desierialize(msgdata);
					this.SimilarProducts = arrayT47.getParam();
				}else if (localName.equalsIgnoreCase("Lists")) {
					heavytest.performence.ArrayOf_xsd_string arrayT48 = (new heavytest.performence.ArrayOf_xsd_string());
					arrayT48.desierialize(msgdata);
					this.Lists = arrayT48.getParam();
				}else if (localName.equalsIgnoreCase("Status")) {
					this.Status= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else
					throw new org.apache.axis.AxisFault("unknown tag find "+ localName);
				org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
		}//end of for loop
		return this;

	}

	public void serialize(org.apache.axis.encoding.SerializationContext context)throws java.io.IOException{
		String m_URI ="http://performence.heavytest";
		String type_name = "Details";
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = false;
		//write the parameters

		context.writeString("<Url>");
		if(this.Url!=null){
			context.writeString(String.valueOf(Url));
		}
		context.writeString("</Url>\n");

		context.writeString("<Asin>");
		if(this.Asin!=null){
			context.writeString(String.valueOf(Asin));
		}
		context.writeString("</Asin>\n");

		context.writeString("<ProductName>");
		if(this.ProductName!=null){
			context.writeString(String.valueOf(ProductName));
		}
		context.writeString("</ProductName>\n");

		context.writeString("<Catalog>");
		if(this.Catalog!=null){
			context.writeString(String.valueOf(Catalog));
		}
		context.writeString("</Catalog>\n");

		context.writeString("<KeyPhrases xsi:type=\"soapenc:Array\" soapenc:arrayType=\"ns2:KeyPhrase[]\" xmlns:ns2 = \"http://performence.heavytest\">");
		if(this.KeyPhrases!=null){
			context.writeString("\n");
			heavytest.performence.ArrayOfKeyPhrase item4 = new heavytest.performence.ArrayOfKeyPhrase();
			item4.setParam(KeyPhrases);
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;
			item4.serialize(context);
		}
		context.writeString("</KeyPhrases>\n");

		context.writeString("<Artists xsi:type=\"soapenc:Array\" soapenc:arrayType=\"ns2:string[]\" xmlns:ns2 = \"http://www.w3.org/2001/XMLSchema\">");
		if(this.Artists!=null){
			context.writeString("\n");
			heavytest.performence.ArrayOf_xsd_string item5 = new heavytest.performence.ArrayOf_xsd_string();
			item5.setParam(Artists);
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;
			item5.serialize(context);
		}
		context.writeString("</Artists>\n");

		context.writeString("<Authors xsi:type=\"soapenc:Array\" soapenc:arrayType=\"ns2:string[]\" xmlns:ns2 = \"http://www.w3.org/2001/XMLSchema\">");
		if(this.Authors!=null){
			context.writeString("\n");
			heavytest.performence.ArrayOf_xsd_string item6 = new heavytest.performence.ArrayOf_xsd_string();
			item6.setParam(Authors);
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;
			item6.serialize(context);
		}
		context.writeString("</Authors>\n");

		context.writeString("<Mpn>");
		if(this.Mpn!=null){
			context.writeString(String.valueOf(Mpn));
		}
		context.writeString("</Mpn>\n");

		context.writeString("<Starring xsi:type=\"soapenc:Array\" soapenc:arrayType=\"ns2:string[]\" xmlns:ns2 = \"http://www.w3.org/2001/XMLSchema\">");
		if(this.Starring!=null){
			context.writeString("\n");
			heavytest.performence.ArrayOf_xsd_string item8 = new heavytest.performence.ArrayOf_xsd_string();
			item8.setParam(Starring);
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;
			item8.serialize(context);
		}
		context.writeString("</Starring>\n");

		context.writeString("<Directors xsi:type=\"soapenc:Array\" soapenc:arrayType=\"ns2:string[]\" xmlns:ns2 = \"http://www.w3.org/2001/XMLSchema\">");
		if(this.Directors!=null){
			context.writeString("\n");
			heavytest.performence.ArrayOf_xsd_string item9 = new heavytest.performence.ArrayOf_xsd_string();
			item9.setParam(Directors);
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;
			item9.serialize(context);
		}
		context.writeString("</Directors>\n");

		context.writeString("<TheatricalReleaseDate>");
		if(this.TheatricalReleaseDate!=null){
			context.writeString(String.valueOf(TheatricalReleaseDate));
		}
		context.writeString("</TheatricalReleaseDate>\n");

		context.writeString("<ReleaseDate>");
		if(this.ReleaseDate!=null){
			context.writeString(String.valueOf(ReleaseDate));
		}
		context.writeString("</ReleaseDate>\n");

		context.writeString("<Manufacturer>");
		if(this.Manufacturer!=null){
			context.writeString(String.valueOf(Manufacturer));
		}
		context.writeString("</Manufacturer>\n");

		context.writeString("<Distributor>");
		if(this.Distributor!=null){
			context.writeString(String.valueOf(Distributor));
		}
		context.writeString("</Distributor>\n");

		context.writeString("<ImageUrlSmall>");
		if(this.ImageUrlSmall!=null){
			context.writeString(String.valueOf(ImageUrlSmall));
		}
		context.writeString("</ImageUrlSmall>\n");

		context.writeString("<ImageUrlMedium>");
		if(this.ImageUrlMedium!=null){
			context.writeString(String.valueOf(ImageUrlMedium));
		}
		context.writeString("</ImageUrlMedium>\n");

		context.writeString("<ImageUrlLarge>");
		if(this.ImageUrlLarge!=null){
			context.writeString(String.valueOf(ImageUrlLarge));
		}
		context.writeString("</ImageUrlLarge>\n");

		context.writeString("<ListPrice>");
		if(this.ListPrice!=null){
			context.writeString(String.valueOf(ListPrice));
		}
		context.writeString("</ListPrice>\n");

		context.writeString("<OurPrice>");
		if(this.OurPrice!=null){
			context.writeString(String.valueOf(OurPrice));
		}
		context.writeString("</OurPrice>\n");

		context.writeString("<UsedPrice>");
		if(this.UsedPrice!=null){
			context.writeString(String.valueOf(UsedPrice));
		}
		context.writeString("</UsedPrice>\n");

		context.writeString("<RefurbishedPrice>");
		if(this.RefurbishedPrice!=null){
			context.writeString(String.valueOf(RefurbishedPrice));
		}
		context.writeString("</RefurbishedPrice>\n");

		context.writeString("<CollectiblePrice>");
		if(this.CollectiblePrice!=null){
			context.writeString(String.valueOf(CollectiblePrice));
		}
		context.writeString("</CollectiblePrice>\n");

		context.writeString("<ThirdPartyNewPrice>");
		if(this.ThirdPartyNewPrice!=null){
			context.writeString(String.valueOf(ThirdPartyNewPrice));
		}
		context.writeString("</ThirdPartyNewPrice>\n");

		context.writeString("<NumberOfOfferings>");
		if(this.NumberOfOfferings!=null){
			context.writeString(String.valueOf(NumberOfOfferings));
		}
		context.writeString("</NumberOfOfferings>\n");

		context.writeString("<ThirdPartyNewCount>");
		if(this.ThirdPartyNewCount!=null){
			context.writeString(String.valueOf(ThirdPartyNewCount));
		}
		context.writeString("</ThirdPartyNewCount>\n");

		context.writeString("<UsedCount>");
		if(this.UsedCount!=null){
			context.writeString(String.valueOf(UsedCount));
		}
		context.writeString("</UsedCount>\n");

		context.writeString("<CollectibleCount>");
		if(this.CollectibleCount!=null){
			context.writeString(String.valueOf(CollectibleCount));
		}
		context.writeString("</CollectibleCount>\n");

		context.writeString("<RefurbishedCount>");
		if(this.RefurbishedCount!=null){
			context.writeString(String.valueOf(RefurbishedCount));
		}
		context.writeString("</RefurbishedCount>\n");

		context.writeString("<ThirdPartyProductInfo>");
		if(this.ThirdPartyProductInfo!=null){
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;
			ThirdPartyProductInfo.serialize(context);
		}
		context.writeString("</ThirdPartyProductInfo>\n");

		context.writeString("<SalesRank>");
		if(this.SalesRank!=null){
			context.writeString(String.valueOf(SalesRank));
		}
		context.writeString("</SalesRank>\n");

		context.writeString("<BrowseList xsi:type=\"soapenc:Array\" soapenc:arrayType=\"ns2:BrowseNode[]\" xmlns:ns2 = \"http://performence.heavytest\">");
		if(this.BrowseList!=null){
			context.writeString("\n");
			heavytest.performence.ArrayOfBrowseNode item30 = new heavytest.performence.ArrayOfBrowseNode();
			item30.setParam(BrowseList);
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;
			item30.serialize(context);
		}
		context.writeString("</BrowseList>\n");

		context.writeString("<Media>");
		if(this.Media!=null){
			context.writeString(String.valueOf(Media));
		}
		context.writeString("</Media>\n");

		context.writeString("<ReadingLevel>");
		if(this.ReadingLevel!=null){
			context.writeString(String.valueOf(ReadingLevel));
		}
		context.writeString("</ReadingLevel>\n");

		context.writeString("<Publisher>");
		if(this.Publisher!=null){
			context.writeString(String.valueOf(Publisher));
		}
		context.writeString("</Publisher>\n");

		context.writeString("<NumMedia>");
		if(this.NumMedia!=null){
			context.writeString(String.valueOf(NumMedia));
		}
		context.writeString("</NumMedia>\n");

		context.writeString("<Isbn>");
		if(this.Isbn!=null){
			context.writeString(String.valueOf(Isbn));
		}
		context.writeString("</Isbn>\n");

		context.writeString("<Features xsi:type=\"soapenc:Array\" soapenc:arrayType=\"ns2:string[]\" xmlns:ns2 = \"http://www.w3.org/2001/XMLSchema\">");
		if(this.Features!=null){
			context.writeString("\n");
			heavytest.performence.ArrayOf_xsd_string item36 = new heavytest.performence.ArrayOf_xsd_string();
			item36.setParam(Features);
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;
			item36.serialize(context);
		}
		context.writeString("</Features>\n");

		context.writeString("<MpaaRating>");
		if(this.MpaaRating!=null){
			context.writeString(String.valueOf(MpaaRating));
		}
		context.writeString("</MpaaRating>\n");

		context.writeString("<EsrbRating>");
		if(this.EsrbRating!=null){
			context.writeString(String.valueOf(EsrbRating));
		}
		context.writeString("</EsrbRating>\n");

		context.writeString("<AgeGroup>");
		if(this.AgeGroup!=null){
			context.writeString(String.valueOf(AgeGroup));
		}
		context.writeString("</AgeGroup>\n");

		context.writeString("<Availability>");
		if(this.Availability!=null){
			context.writeString(String.valueOf(Availability));
		}
		context.writeString("</Availability>\n");

		context.writeString("<Upc>");
		if(this.Upc!=null){
			context.writeString(String.valueOf(Upc));
		}
		context.writeString("</Upc>\n");

		context.writeString("<Tracks xsi:type=\"soapenc:Array\" soapenc:arrayType=\"ns2:Track[]\" xmlns:ns2 = \"http://performence.heavytest\">");
		if(this.Tracks!=null){
			context.writeString("\n");
			heavytest.performence.ArrayOfTrack item42 = new heavytest.performence.ArrayOfTrack();
			item42.setParam(Tracks);
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;
			item42.serialize(context);
		}
		context.writeString("</Tracks>\n");

		context.writeString("<Accessories xsi:type=\"soapenc:Array\" soapenc:arrayType=\"ns2:string[]\" xmlns:ns2 = \"http://www.w3.org/2001/XMLSchema\">");
		if(this.Accessories!=null){
			context.writeString("\n");
			heavytest.performence.ArrayOf_xsd_string item43 = new heavytest.performence.ArrayOf_xsd_string();
			item43.setParam(Accessories);
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;
			item43.serialize(context);
		}
		context.writeString("</Accessories>\n");

		context.writeString("<Platforms xsi:type=\"soapenc:Array\" soapenc:arrayType=\"ns2:string[]\" xmlns:ns2 = \"http://www.w3.org/2001/XMLSchema\">");
		if(this.Platforms!=null){
			context.writeString("\n");
			heavytest.performence.ArrayOf_xsd_string item44 = new heavytest.performence.ArrayOf_xsd_string();
			item44.setParam(Platforms);
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;
			item44.serialize(context);
		}
		context.writeString("</Platforms>\n");

		context.writeString("<Encoding>");
		if(this.Encoding!=null){
			context.writeString(String.valueOf(Encoding));
		}
		context.writeString("</Encoding>\n");

		context.writeString("<Reviews>");
		if(this.Reviews!=null){
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;
			Reviews.serialize(context);
		}
		context.writeString("</Reviews>\n");

		context.writeString("<SimilarProducts xsi:type=\"soapenc:Array\" soapenc:arrayType=\"ns2:string[]\" xmlns:ns2 = \"http://www.w3.org/2001/XMLSchema\">");
		if(this.SimilarProducts!=null){
			context.writeString("\n");
			heavytest.performence.ArrayOf_xsd_string item47 = new heavytest.performence.ArrayOf_xsd_string();
			item47.setParam(SimilarProducts);
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;
			item47.serialize(context);
		}
		context.writeString("</SimilarProducts>\n");

		context.writeString("<Lists xsi:type=\"soapenc:Array\" soapenc:arrayType=\"ns2:string[]\" xmlns:ns2 = \"http://www.w3.org/2001/XMLSchema\">");
		if(this.Lists!=null){
			context.writeString("\n");
			heavytest.performence.ArrayOf_xsd_string item48 = new heavytest.performence.ArrayOf_xsd_string();
			item48.setParam(Lists);
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;
			item48.serialize(context);
		}
		context.writeString("</Lists>\n");

		context.writeString("<Status>");
		if(this.Status!=null){
			context.writeString(String.valueOf(Status));
		}
		context.writeString("</Status>\n");

	}

	public void setUrl(java.lang.String Url){
		this.Url = Url;
	}
	public java.lang.String getUrl(){
		return Url;
	}
	public void setAsin(java.lang.String Asin){
		this.Asin = Asin;
	}
	public java.lang.String getAsin(){
		return Asin;
	}
	public void setProductName(java.lang.String ProductName){
		this.ProductName = ProductName;
	}
	public java.lang.String getProductName(){
		return ProductName;
	}
	public void setCatalog(java.lang.String Catalog){
		this.Catalog = Catalog;
	}
	public java.lang.String getCatalog(){
		return Catalog;
	}
	public void setKeyPhrases(heavytest.performence.KeyPhrase[] KeyPhrases){
		this.KeyPhrases = KeyPhrases;
	}
	public heavytest.performence.KeyPhrase[] getKeyPhrases(){
		return KeyPhrases;
	}
	public void setArtists(java.lang.String[] Artists){
		this.Artists = Artists;
	}
	public java.lang.String[] getArtists(){
		return Artists;
	}
	public void setAuthors(java.lang.String[] Authors){
		this.Authors = Authors;
	}
	public java.lang.String[] getAuthors(){
		return Authors;
	}
	public void setMpn(java.lang.String Mpn){
		this.Mpn = Mpn;
	}
	public java.lang.String getMpn(){
		return Mpn;
	}
	public void setStarring(java.lang.String[] Starring){
		this.Starring = Starring;
	}
	public java.lang.String[] getStarring(){
		return Starring;
	}
	public void setDirectors(java.lang.String[] Directors){
		this.Directors = Directors;
	}
	public java.lang.String[] getDirectors(){
		return Directors;
	}
	public void setTheatricalReleaseDate(java.lang.String TheatricalReleaseDate){
		this.TheatricalReleaseDate = TheatricalReleaseDate;
	}
	public java.lang.String getTheatricalReleaseDate(){
		return TheatricalReleaseDate;
	}
	public void setReleaseDate(java.lang.String ReleaseDate){
		this.ReleaseDate = ReleaseDate;
	}
	public java.lang.String getReleaseDate(){
		return ReleaseDate;
	}
	public void setManufacturer(java.lang.String Manufacturer){
		this.Manufacturer = Manufacturer;
	}
	public java.lang.String getManufacturer(){
		return Manufacturer;
	}
	public void setDistributor(java.lang.String Distributor){
		this.Distributor = Distributor;
	}
	public java.lang.String getDistributor(){
		return Distributor;
	}
	public void setImageUrlSmall(java.lang.String ImageUrlSmall){
		this.ImageUrlSmall = ImageUrlSmall;
	}
	public java.lang.String getImageUrlSmall(){
		return ImageUrlSmall;
	}
	public void setImageUrlMedium(java.lang.String ImageUrlMedium){
		this.ImageUrlMedium = ImageUrlMedium;
	}
	public java.lang.String getImageUrlMedium(){
		return ImageUrlMedium;
	}
	public void setImageUrlLarge(java.lang.String ImageUrlLarge){
		this.ImageUrlLarge = ImageUrlLarge;
	}
	public java.lang.String getImageUrlLarge(){
		return ImageUrlLarge;
	}
	public void setListPrice(java.lang.String ListPrice){
		this.ListPrice = ListPrice;
	}
	public java.lang.String getListPrice(){
		return ListPrice;
	}
	public void setOurPrice(java.lang.String OurPrice){
		this.OurPrice = OurPrice;
	}
	public java.lang.String getOurPrice(){
		return OurPrice;
	}
	public void setUsedPrice(java.lang.String UsedPrice){
		this.UsedPrice = UsedPrice;
	}
	public java.lang.String getUsedPrice(){
		return UsedPrice;
	}
	public void setRefurbishedPrice(java.lang.String RefurbishedPrice){
		this.RefurbishedPrice = RefurbishedPrice;
	}
	public java.lang.String getRefurbishedPrice(){
		return RefurbishedPrice;
	}
	public void setCollectiblePrice(java.lang.String CollectiblePrice){
		this.CollectiblePrice = CollectiblePrice;
	}
	public java.lang.String getCollectiblePrice(){
		return CollectiblePrice;
	}
	public void setThirdPartyNewPrice(java.lang.String ThirdPartyNewPrice){
		this.ThirdPartyNewPrice = ThirdPartyNewPrice;
	}
	public java.lang.String getThirdPartyNewPrice(){
		return ThirdPartyNewPrice;
	}
	public void setNumberOfOfferings(java.lang.String NumberOfOfferings){
		this.NumberOfOfferings = NumberOfOfferings;
	}
	public java.lang.String getNumberOfOfferings(){
		return NumberOfOfferings;
	}
	public void setThirdPartyNewCount(java.lang.String ThirdPartyNewCount){
		this.ThirdPartyNewCount = ThirdPartyNewCount;
	}
	public java.lang.String getThirdPartyNewCount(){
		return ThirdPartyNewCount;
	}
	public void setUsedCount(java.lang.String UsedCount){
		this.UsedCount = UsedCount;
	}
	public java.lang.String getUsedCount(){
		return UsedCount;
	}
	public void setCollectibleCount(java.lang.String CollectibleCount){
		this.CollectibleCount = CollectibleCount;
	}
	public java.lang.String getCollectibleCount(){
		return CollectibleCount;
	}
	public void setRefurbishedCount(java.lang.String RefurbishedCount){
		this.RefurbishedCount = RefurbishedCount;
	}
	public java.lang.String getRefurbishedCount(){
		return RefurbishedCount;
	}
	public void setThirdPartyProductInfo(heavytest.performence.ThirdPartyProductInfo ThirdPartyProductInfo){
		this.ThirdPartyProductInfo = ThirdPartyProductInfo;
	}
	public heavytest.performence.ThirdPartyProductInfo getThirdPartyProductInfo(){
		return ThirdPartyProductInfo;
	}
	public void setSalesRank(java.lang.String SalesRank){
		this.SalesRank = SalesRank;
	}
	public java.lang.String getSalesRank(){
		return SalesRank;
	}
	public void setBrowseList(heavytest.performence.BrowseNode[] BrowseList){
		this.BrowseList = BrowseList;
	}
	public heavytest.performence.BrowseNode[] getBrowseList(){
		return BrowseList;
	}
	public void setMedia(java.lang.String Media){
		this.Media = Media;
	}
	public java.lang.String getMedia(){
		return Media;
	}
	public void setReadingLevel(java.lang.String ReadingLevel){
		this.ReadingLevel = ReadingLevel;
	}
	public java.lang.String getReadingLevel(){
		return ReadingLevel;
	}
	public void setPublisher(java.lang.String Publisher){
		this.Publisher = Publisher;
	}
	public java.lang.String getPublisher(){
		return Publisher;
	}
	public void setNumMedia(java.lang.String NumMedia){
		this.NumMedia = NumMedia;
	}
	public java.lang.String getNumMedia(){
		return NumMedia;
	}
	public void setIsbn(java.lang.String Isbn){
		this.Isbn = Isbn;
	}
	public java.lang.String getIsbn(){
		return Isbn;
	}
	public void setFeatures(java.lang.String[] Features){
		this.Features = Features;
	}
	public java.lang.String[] getFeatures(){
		return Features;
	}
	public void setMpaaRating(java.lang.String MpaaRating){
		this.MpaaRating = MpaaRating;
	}
	public java.lang.String getMpaaRating(){
		return MpaaRating;
	}
	public void setEsrbRating(java.lang.String EsrbRating){
		this.EsrbRating = EsrbRating;
	}
	public java.lang.String getEsrbRating(){
		return EsrbRating;
	}
	public void setAgeGroup(java.lang.String AgeGroup){
		this.AgeGroup = AgeGroup;
	}
	public java.lang.String getAgeGroup(){
		return AgeGroup;
	}
	public void setAvailability(java.lang.String Availability){
		this.Availability = Availability;
	}
	public java.lang.String getAvailability(){
		return Availability;
	}
	public void setUpc(java.lang.String Upc){
		this.Upc = Upc;
	}
	public java.lang.String getUpc(){
		return Upc;
	}
	public void setTracks(heavytest.performence.Track[] Tracks){
		this.Tracks = Tracks;
	}
	public heavytest.performence.Track[] getTracks(){
		return Tracks;
	}
	public void setAccessories(java.lang.String[] Accessories){
		this.Accessories = Accessories;
	}
	public java.lang.String[] getAccessories(){
		return Accessories;
	}
	public void setPlatforms(java.lang.String[] Platforms){
		this.Platforms = Platforms;
	}
	public java.lang.String[] getPlatforms(){
		return Platforms;
	}
	public void setEncoding(java.lang.String Encoding){
		this.Encoding = Encoding;
	}
	public java.lang.String getEncoding(){
		return Encoding;
	}
	public void setReviews(heavytest.performence.Reviews Reviews){
		this.Reviews = Reviews;
	}
	public heavytest.performence.Reviews getReviews(){
		return Reviews;
	}
	public void setSimilarProducts(java.lang.String[] SimilarProducts){
		this.SimilarProducts = SimilarProducts;
	}
	public java.lang.String[] getSimilarProducts(){
		return SimilarProducts;
	}
	public void setLists(java.lang.String[] Lists){
		this.Lists = Lists;
	}
	public java.lang.String[] getLists(){
		return Lists;
	}
	public void setStatus(java.lang.String Status){
		this.Status = Status;
	}
	public java.lang.String getStatus(){
		return Status;
	}
}
