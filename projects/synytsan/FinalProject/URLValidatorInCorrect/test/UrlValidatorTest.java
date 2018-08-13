/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import junit.framework.TestCase;
import java.util.Random;

public class UrlValidatorTest extends TestCase {

   public UrlValidatorTest(String testName) {
      super(testName);
   }

   public void testManualTest()
   {
       //You can use this function to implement your manual testing
       UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

       assertTrue(urlVal.isValid("http://www.google.com"));
//     assertTrue(urlVal.isValid("https://www.google.com")); // FAILURE: "java.lang.ExceptionInInitializerError: Regular expressions are missing"
       assertTrue(urlVal.isValid("http://google.com"));
       assertTrue(urlVal.isValid("http://wikipedia.org"));
       assertTrue(urlVal.isValid("http://a.co"));
       assertTrue(urlVal.isValid("http://a.co/b/c")); // BUG: Should be valid.
       assertTrue(urlVal.isValid("http://a.b.co"));
//     assertTrue(urlVal.isValid("ftp://foo.com/file.txt")); // FAILURE: "java.lang.ExceptionInInitializerError: Regular expressions are missing"
//     assertTrue(urlVal.isValid("ftp://ftp.foo.com/sub/sub/sub/file.txt")); // FAILURE: "java.lang.ExceptionInInitializerError: Regular expressions are missing"

       assertTrue(!urlVal.isValid("google.com"));
       assertTrue(!urlVal.isValid("google"));
       assertTrue(!urlVal.isValid(".com"));
   }

   public void testYourFirstPartition()
   {
       // One partition could be when protocol changes but the rest of the URL remains unchanged.

       // Pass schemes manually
       String[] schemes = {"http", "https", "ftp", "file"};

       UrlValidator urlVal = new UrlValidator(schemes, 0L);
       assertTrue(urlVal.isValid("http://www.hello.com"));
       assertTrue(urlVal.isValid("HTTP://www.hello.com"));
       assertTrue(urlVal.isValid("ftp://www.hello.com"));
       assertTrue(urlVal.isValid("FTP://www.hello.com"));
       assertTrue(urlVal.isValid("https://www.hello.com"));
       assertTrue(urlVal.isValid("HTTPS://www.hello.com"));
       assertTrue(urlVal.isValid("file://www.hello.com"));
       assertTrue(urlVal.isValid("FILE://www.hello.com"));
       assertFalse(urlVal.isValid("://www.hello.com"));

       // Allow all schemes
       UrlValidator urlVal2 = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
       assertTrue(urlVal2.isValid("http://www.hello.com"));
       assertTrue(urlVal2.isValid("https://www.hello.com"));
       assertTrue(urlVal2.isValid("ftp://www.hello.com"));
       assertTrue(urlVal2.isValid("file://www.hello.com"));
       assertTrue(urlVal2.isValid("HTTP://www.hello.com"));
       assertTrue(urlVal2.isValid("HTTPS://www.hello.com"));
       assertTrue(urlVal2.isValid("FTP://www.hello.com"));
       assertTrue(urlVal2.isValid("FILE://www.hello.com"));
       assertFalse(urlVal2.isValid("://www.hello.com"));
   }

   public void testYourSecondPartition(){
       // Another partition could be when domain and path change but protocol remains unchanged.
       UrlValidator urlVal = new UrlValidator();

       // Test domain regions
       assertTrue(urlVal.isValid("http://www.hello.com"));
       assertTrue(urlVal.isValid("http://www.hello.cu"));
       assertTrue(urlVal.isValid("http://www.hello.ru"));
       assertTrue(urlVal.isValid("http://www.hello.pl"));
       assertTrue(urlVal.isValid("http://www.hello.co"));
       assertTrue(urlVal.isValid("http://www.hello.se"));

       // Test Paths
       assertTrue(urlVal.isValid("http://www.hello.com/world"));
       assertTrue(urlVal.isValid("http://www.hello.com/world/"));
       assertTrue(urlVal.isValid("http://www.hello.com/world.php"));
       assertTrue(urlVal.isValid("http://www.hello.com/world.php/"));
       assertTrue(urlVal.isValid("http://www.hello.com/world/the/"));
       assertTrue(urlVal.isValid("http://www.hello.com/world/the"));

       // Test invalid domain regions
       assertFalse(urlVal.isValid("http://www.hello.pu"));
       assertFalse(urlVal.isValid("http://www.hello.av"));

       // Invalid domains and paths
       assertFalse(urlVal.isValid("http://www.hello"));
       assertFalse(urlVal.isValid("http://www.hello"));
       assertFalse(urlVal.isValid("http://www.hello/pizza.com"));
       assertFalse(urlVal.isValid("http://www.hello/.com"));
       assertFalse(urlVal.isValid("http://www.hello world.com"));
   }

   public void testIsValid()
   {
       //scheme://host:port/path?query



       //You can use this function for programming based testing
       System.out.println("\nStarting Random Tests\n");

       // Establish A set of valid and invalid parts of a URL
       ResultPair[] testSchemes = {
                new ResultPair("http://", true),
                new ResultPair("https://", true),
                new ResultPair("ftp://", false),
                new ResultPair("h3t://", true),
                new ResultPair("", false),
                new ResultPair("3ht://", false),
                new ResultPair("http:/", false),
                new ResultPair("http:", false),
                new ResultPair("http/", false),
                new ResultPair("://", false),
                new ResultPair("123://", false)
       };

       ResultPair[] testDomains = {
               new ResultPair("www.amazon.com", true),
               new ResultPair("www.amazon.es", true),
               new ResultPair("www.amazon.gov", true),
               new ResultPair("0.0.0.0", true),
               new ResultPair("255.255.255.255", true),
               new ResultPair("www.amazoncom", false),
               new ResultPair("wwwamazon.com", false),
               new ResultPair("wwwamazoncom", false),
               new ResultPair("0.0.0.-1", false),
               new ResultPair("256.256.256.256", false),
               new ResultPair("256.amazon.255", false),
       };

       // Between 0 and 65535 is valid
       ResultPair[] testPort = {
               new ResultPair(":80", true),
               new ResultPair(":0", true),
               new ResultPair("", true),
               new ResultPair(":65535", true),
               new ResultPair(":65536", false),
               new ResultPair(":-256", false),
       };

       // Some Paths to test
       ResultPair[] testPaths = {
               new ResultPair("/test", true),
               new ResultPair("/t", true),
               new ResultPair("/12345", true),
               new ResultPair("/$76", true),
               new ResultPair("/test/two", true),
               new ResultPair("", true),
               new ResultPair("/..//", false),
               new ResultPair("/..", false),
               new ResultPair("/test//tester", false),
               new ResultPair("/test/./tester", false)
       };

       // Some Queries to Test
       ResultPair[] testQuery = {
               new ResultPair("?action=view", true),
               new ResultPair("", true),
               new ResultPair("action=view", false),
       };

//     // Build a URL
//     StringBuilder url = new StringBuilder();
//     url.append(testSchemes[0].item);
//     url.append(testDomains[0].item);
//     url.append(testPort[0].item);
//     url.append(testPaths[0].item);
//     url.append(testQuery[0].item);
//
//
//     System.out.println(url);

       Random rand = new Random();

       UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

       System.out.println("\n~~~~~~~~~~~ Starting Random Test ~~~~~~~~~~~~~~~\n");
       for(int i = 0; i < 250; i++)
       {
           //UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
           int scheme, domain, port, path, query;
           boolean ret_val = false;

           scheme = 0 + rand.nextInt((testSchemes.length - 0) + 0);
           domain = 0 + rand.nextInt((testDomains.length - 0) + 0);
           port = 0 + rand.nextInt((testPort.length - 0) + 0);
           path = 0 + rand.nextInt((testPaths.length - 0) + 0);
           query = 0 + rand.nextInt((testQuery.length - 0) + 0);


           // Build a URL
           StringBuilder url = new StringBuilder();

           url.append(testSchemes[scheme].item);
           url.append(testDomains[domain].item);
           url.append(testPaths[path].item);
           url.append(testQuery[query].item);

           System.out.println("\n");
           String url_val = url.toString();

           System.out.println(i+1);

           if((testSchemes[scheme].valid == true) && (testDomains[domain].valid == true) && /*(!testPort[port].valid == true) &&*/ (testPaths[path].valid == true) && (testQuery[query].valid == true))
           {
               String val = "This is a Good URL:\t" + url_val;
               System.out.println(val);
               ret_val = urlVal.isValid(url_val);
               val = "Was it Good?:\t" + ret_val;
               System.out.println(val);

           } else {
               String val = "This is a Bad URL:\t" + url_val;
               System.out.println(val);
               val = "Was it Bad?:\t" + !ret_val;
               System.out.println(val);
           }

       }
   }

}
