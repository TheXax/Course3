using lab2;

var kazakh = Entropy.ReadFromFile("kazakh.txt");
var spanish = Entropy.ReadFromFile("spanish.txt");
var binary = Entropy.ReadFromFile("binary.txt");
var myName = Entropy.ReadFromFile("myName.txt");
var myNameASCII = Entropy.ReadFromFile("myNameASCII.txt");


Console.WriteLine("\n==========================================");
Console.WriteLine($"Entropy of Language (kazakh):      {Entropy.GetShannonEntropy(kazakh)}");
Console.WriteLine($"Entropy of Language (spanish):  {Entropy.GetShannonEntropy(spanish)}");
Console.WriteLine($"Entropy of Language (binary):      {Entropy.GetShannonEntropy(binary)}");

Console.WriteLine("\n================  P = 0  =================");
Console.WriteLine($"Information Amount (kazakh):       {Entropy.GetInformationAmount(kazakh, myName)}");
Console.WriteLine($"Information Amount (spanish):   {Entropy.GetInformationAmount(spanish, myName)}");
Console.WriteLine($"Information Amount (ASCII):        {Entropy.GetInformationAmount(myNameASCII, myNameASCII)}");

Console.WriteLine("\n===============  P = 0.1  ================");
Console.WriteLine($"Information Amount (kazakh):       {Entropy.GetInformationAmount(kazakh, myName, 0.1)}");
Console.WriteLine($"Information Amount (spanish):   {Entropy.GetInformationAmount(spanish, myName, 0.1)}");
Console.WriteLine($"Information Amount (ASCII):        {Entropy.GetInformationAmount(myNameASCII, myNameASCII, 0.1)}");

Console.WriteLine("\n===============  P = 0.5  ================");
Console.WriteLine($"Information Amount (kazakh):       {Entropy.GetInformationAmount(kazakh, myName, 0.5)}");
Console.WriteLine($"Information Amount (spanish):   {Entropy.GetInformationAmount(spanish, myName, 0.5)}");
Console.WriteLine($"Information Amount (ASCII):        {Entropy.GetInformationAmount(myNameASCII, myNameASCII, 0.5)}");

Console.WriteLine("\n================  P = 1  =================");
Console.WriteLine($"Information Amount (kazakh):       {Entropy.GetInformationAmount(kazakh, myName, 1)}");
Console.WriteLine($"Information Amount (spanish):   {Entropy.GetInformationAmount(spanish, myName, 1)}");
Console.WriteLine($"Information Amount (ASCII):        {Entropy.GetInformationAmount(myNameASCII, myNameASCII, 1)}");
