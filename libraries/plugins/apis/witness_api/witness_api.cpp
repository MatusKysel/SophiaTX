#include <sophiatx/plugins/witness_api/witness_api_plugin.hpp>
#include <sophiatx/plugins/witness_api/witness_api.hpp>

namespace sophiatx { namespace plugins { namespace witness {

namespace detail {

class witness_api_impl
{
   public:
      witness_api_impl(witness_api_plugin & plugin) : _app(plugin.app()), _db( plugin.app()->get_plugin< sophiatx::plugins::chain::chain_plugin >().db() ) {}

      DECLARE_API_IMPL(
         (get_account_bandwidth)
         (get_reserve_ratio)
      )

      appbase::application* _app;   
      std::shared_ptr<database_interface> _db;
};

DEFINE_API_IMPL( witness_api_impl, get_account_bandwidth )
{
   get_account_bandwidth_return result;

   auto band = _db->find< witness::account_bandwidth_object, witness::by_account_bandwidth_type >( boost::make_tuple( args.account, args.type ) );
   if( band != nullptr )
      result.bandwidth = *band;

   return result;
}

DEFINE_API_IMPL( witness_api_impl, get_reserve_ratio )
{
   return _db->get( reserve_ratio_id_type() );
}

} // detail

witness_api::witness_api(witness_api_plugin & plugin): my( new detail::witness_api_impl(plugin) )
{
   JSON_RPC_REGISTER_API( SOPHIATX_WITNESS_API_PLUGIN_NAME, plugin.app() );
}

witness_api::~witness_api() 
{
   JSON_RPC_DEREGISTER_API( SOPHIATX_WITNESS_API_PLUGIN_NAME, my->_app );
}

DEFINE_READ_APIS( witness_api,
   (get_account_bandwidth)
   (get_reserve_ratio)
)

} } } // sophiatx::plugins::witness
