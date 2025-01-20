using Microsoft.AspNetCore.Http;
using System.Text.Json;

namespace UWSR.Utils
{


    public static class SessionExtensions
    {
        public static void Set<T>(this ISession session, string key, T value)
        {
            session.SetString(key, JsonSerializer.Serialize(value)); //сохраняется в сессии под указанным ключом key
        }

        public static T Get<T>(this ISession session, string key)
        {
            var value = session.GetString(key);
            return value == null ? default(T) : JsonSerializer.Deserialize<T>(value);
        }
    }

}
