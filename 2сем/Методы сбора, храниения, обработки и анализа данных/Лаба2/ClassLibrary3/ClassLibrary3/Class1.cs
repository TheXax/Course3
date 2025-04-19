using System;
using System.Data.SqlTypes;
using System.IO;
using Microsoft.SqlServer.Server;

namespace ClassLibrary3
{ 
    public class FileReader
    {
        [SqlProcedure]
        public static void ReadFile(SqlString filePath, out SqlString fileContent)
        {
            try
            {
                
                string content = File.ReadAllText(filePath.Value);
                fileContent = new SqlString(content);
            }
            catch (Exception ex)
            {
               
                fileContent = new SqlString($"Ошибка: {ex.Message}");
            }
        }
    }
}