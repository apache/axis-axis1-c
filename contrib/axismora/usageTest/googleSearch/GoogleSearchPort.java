package googleSearch;
/**
* This is the service class build with the information given
 * by the wsdl file the user should fill the logic here 
 */
public class GoogleSearchPort  {
	public byte[] doGetCachedPage(java.lang.String param0,java.lang.String param1){return new byte[]{Byte.parseByte("a")};}
	public java.lang.String doSpellingSuggestion(java.lang.String param0,java.lang.String param1){return "spell";}
	public googleSearch.GoogleSearchResult doGoogleSearch(java.lang.String param0,boolean param1,int param2,java.lang.String param3,java.lang.String param4,boolean param5,java.lang.String param6,java.lang.String param7,int param8,java.lang.String param9){return new googleSearch.GoogleSearchResult();}
}
