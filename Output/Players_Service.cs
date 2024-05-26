using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization;
using System.Data.SqlClient;

public class Players_Service : IPlayers_Repository 
{ 
    public Players_DTO GetById(int id) 
    {
        using (Players_BE be = new Players_BE())
        {
            return be.GetById(id);
        }
    }

    public List<Players_DTO> GetAll() 
    {
        using (Players_BE be = new Players_BE())
        {
            return be.GetAll();
        }
    }

    public void Insert(Players_DTO item) 
    {
        using (Players_BE be = new Players_BE(item))
        {
            be.Insert(item);
        }
    }

    public void Update(Players_DTO item) 
    {
        using (Players_BE be = new Players_BE(item))
        {
            be.Update(item);
        }
    }

    public void Delete(int id) 
    {
        using (Players_BE be = new Players_BE())
        {
            be.Delete(id);
        }
    }
} 
