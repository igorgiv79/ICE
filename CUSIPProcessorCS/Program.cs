using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CUSIPProcessorCS
{
    internal class Program
    {
        static void PrintPrice (float price)
        {
            if (price == -1)
                Console.WriteLine("N/A");
            else
                Console.WriteLine(price);
        }

        static int Main (string[] args)
        {
            if (args.Length == 0)
            {
                Console.Error.WriteLine("Usage: CUSIPProcessorCS.exe <input file name>");
                return -1;
            }

            try
            {
                string file = args[0];
                using (StreamReader reader = new StreamReader(file))
                {
                    string ln = reader.ReadLine();
                    if (String.IsNullOrEmpty(ln))
                    {
                        Console.Error.WriteLine("ERROR: Input is empty");
                        return -2;
                    }

                    // print CUSIP;
                    Console.Write("{0} : ", ln);

                    // go through the prices until we get to the latest one;
                    float latest = -1;
                    while (!reader.EndOfStream)
                    {
                        // read the price;
                        string s = reader.ReadLine();
                        if (float.TryParse(s, out float f) == false)
                        {
                            // no, it is not convertible to float so it must be a CUSIP;
                            PrintPrice(latest);
                            latest = -1;

                            // print the next CUSIP;
                            Console.Write("{0} : ", s);
                        }
                        else
                        {
                            latest = f;
                        }
                    }

                    PrintPrice(latest);
                }
            }
            catch (System.IO.FileNotFoundException e)
            {
                Console.Error.WriteLine("ERROR: file {0} does not exist", e.FileName);
            }
            catch (Exception e)
            {
                Console.Error.WriteLine("ERROR: {0}", e);
            }

            return 0;
        }
    }
}
