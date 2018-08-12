import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
	   UrlValidator urlVal = new UrlValidator();
	   assertTrue(urlVal.isValid("http://www.hello.com"));
	   assertTrue(urlVal.isValid("http://www.hello.com/"));
	   assertTrue(urlVal.isValid("http://www.h.e.l.l.o.com/"));
	   assertTrue(urlVal.isValid("http://www.hello.com/world"));
	   assertTrue(urlVal.isValid("http://русскоерадио.рф"));
	   assertTrue(urlVal.isValid("https://русскоерадио.рф"));
	   assertFalse(urlVal.isValid("http://www.hello/world/.com"));
	   assertFalse(urlVal.isValid("http://www..hello.com/"));
	   assertFalse(urlVal.isValid("http://www.hel lo.com/"));
	   assertFalse(urlVal.isValid("http:// www.hello.com"));
	   assertFalse(urlVal.isValid("http:// www.hello.com"));
	   assertFalse(urlVal.isValid("http:// www.hello.world"));
   }
   
   
    
   public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing	   

   }
   
   public void testYourSecondPartition(){
		 //You can use this function to implement your Second Partition testing	   

   }
   //You need to create more test cases for your Partitions if you need to 
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }
   


}
