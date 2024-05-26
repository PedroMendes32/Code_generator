using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization;
using System.Data.SqlClient;

public class Players_BE : Players_DTO, IDisposable 
{ 
    public Players_BE()
    {

    }
    public Players_BE( Players_DTO obj )
    {
       this.player_id = obj.player_id;
       this.username = obj.username;
       this.email = obj.email;
       this.password = obj.password;
       this.created_at = obj.created_at;
       this.last_login = obj.last_login;
       this.level = obj.level;
       this.experience = obj.experience;
       this.coins = obj.coins;
       this.is_active = obj.is_active;
    }

    public Players_DTO GetById(int id) 
    {
        using (Players_DAO dao = new Players_DAO())
        {
            return dao.GetById(id);
        }
    }

    public List<Players_DTO> GetAll() 
    {
        using (Players_DAO dao = new Players_DAO())
        {
            return dao.GetAll();
        }
    }

    public void Insert(Players_DTO item) 
    {
        using (Players_DAO dao = new Players_DAO())
        {
            dao.Insert(item);
        }
    }

    public void Update(Players_DTO item) 
    {
        using (Players_DAO dao = new Players_DAO())
        {
            dao.Update(item);
        }
    }

    public void Delete(int id) 
    {
        using (Players_DAO dao = new Players_DAO())
        {
            dao.Delete(id);
        }
    }

    public void Dispose() 
    {
        throw new NotImplementedException();
    }
} 
