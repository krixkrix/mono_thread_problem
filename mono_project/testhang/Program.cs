using System;

namespace mytest
{
    class MainClass
    {
        public void Foo()
        {
            for (int i = 1; i<= 10; i++)
            {
                Console.WriteLine(String.Format("Allocate {0} of 10", i));
                byte[] pixels = new byte[1000000];  // size affects when the thread hangs
            }
            Console.WriteLine("Done");
            return;
        }

        private static void Main(string[] args)
        {
        }
    }
}
