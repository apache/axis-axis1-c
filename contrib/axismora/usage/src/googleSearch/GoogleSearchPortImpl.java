package googleSearch;
/**
* This is the service class build with the information given
 * by the wsdl file the user should fill the logic here 
 */
public class GoogleSearchPortImpl  {
	public org.apache.axismora.wrappers.simpleType.Base64ByteArrayParam doGetCachedPage(java.lang.String param0,java.lang.String param1){
		return new org.apache.axismora.wrappers.simpleType.Base64ByteArrayParam("Hello");
	
	}
	public java.lang.String doSpellingSuggestion(java.lang.String param0,java.lang.String param1){
		return "Hi";
	}
	public googleSearch.GoogleSearchResult doGoogleSearch(boolean param0,java.lang.String param1,java.lang.String param2,int param3,java.lang.String param4,boolean param5,java.lang.String param6,int param7,java.lang.String param8,java.lang.String param9){
		return new googleSearch.GoogleSearchResult();
	}
}
