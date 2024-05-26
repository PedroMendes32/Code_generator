using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization;
using System.Data.SqlClient;

public interface IPlayers_Repository 
{ 
    Players_DTO GetById(int id); 
    List<Players_DTO> GetAll(); 
    void Insert(Players_DTO item); 
    void Update(Players_DTO item); 
    void Delete(int id); 
} 
