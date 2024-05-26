using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization;
using System.Data.SqlClient;

public abstract class Database : IDisposable
{
   protected SqlConnection conn;
   private bool disposed = false;

   public Database()
   {
      string connectionString = "Coloque_sua_string_aqui";
      conn = new SqlConnection(connectionString);
      conn.Open();
   }

   protected virtual void Dispose(bool disposing)
   {
      if (!disposed)
      {
         if (disposing)
         {
            if (conn != null)
            {
               conn.Close();
               conn = null;
            }
         }
         disposed = true;
      }
   }

   public void Dispose()
   {
      Dispose(true);
      GC.SuppressFinalize(this);
   }

   ~Database()
   {
      Dispose(false);
   }
}
