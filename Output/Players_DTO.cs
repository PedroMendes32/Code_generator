using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization;
using System.Data.SqlClient;

[DataContract]
public class Players_DTO 
{ 
   [DataMember]
   public int player_id { get; set; }

   [DataMember]
   public string username { get; set; }

   [DataMember]
   public string email { get; set; }

   [DataMember]
   public string password { get; set; }

   [DataMember]
   public DateTime created_at { get; set; }

   [DataMember]
   public DateTime last_login { get; set; }

   [DataMember]
   public int level { get; set; }

   [DataMember]
   public short? experience { get; set; }

   [DataMember]
   public long? coins { get; set; }

   [DataMember]
   public bool is_active { get; set; }

   public Players_DTO()
   {

   }

   public Players_DTO( Players_DTO obj )
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
}
