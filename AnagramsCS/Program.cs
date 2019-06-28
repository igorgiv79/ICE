using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AnagramsCS
{
    class Program {
        static int Main(string[] args)
        {
            Console.WriteLine("Please enter a group of English words, separated by space:");
            string text = Console.ReadLine();
            if (String.IsNullOrEmpty(text)) {
                Console.WriteLine("No input provided");
                return -1;
            }

            string[] words = text.Split(' ');
            foreach (var w1 in words) {
                // discard empty strings;
                if (w1.Length == 0)
                    continue;
                Console.Write("anagrams for {0}:", w1);
                foreach (var w2 in words) {
                    // ignore duplicates
                    if (w1 == w2)
                        continue;
                    // discard words that are different in length;
                    if (w1.Length != w2.Length)
                        continue;
                    // for each character in w1 check that it is present exactly once in w2;
                    bool anagram = true;
                    foreach (var c in w1) {
                        int numOcc1 = w1.Count(f => f == c);
                        int numOcc2 = w2.Count(f => f == c);
                        if (numOcc1 == numOcc2) {
                            continue;
                        }
                        else {
                            // not an anagram;
                            anagram = false;
                            break;
                        }
                    }

                    if (anagram) {
                        Console.Write(" {0}", w2);
                    }
                }
                Console.WriteLine();
            }

            return 0;
        }
    }
}
