<template>
  <div style="color:white">
    <v-row justify="center">
      <v-avatar  style="padding:0;" color="primary"  size="100">
        <img v-bind:src="url + '/avatar/' + id" style="width:100%"/>
      </v-avatar>
    </v-row>
    <div class="mb-4" id="nav">
      <b-nav tabs class="justify-content-center">
          <b-nav-item> <a href="javascript:void(0);" :class="{ 'router-link-exact-active': edit }" @click="edit=true; histo=false"> Modifier Profil </a></b-nav-item>
          <b-nav-item> <a href="javascript:void(0);" :class="{ 'router-link-exact-active': histo }" @click="loadHisto(); edit=false; histo=true"> Historique </a></b-nav-item>
      </b-nav>
    </div>          
    <profile-main v-if="edit"></profile-main>
    <history-table v-if="histo" :entries="entries"/>
  </div>
</template>

<script>
import { mapGetters } from 'vuex';
import ProfileMain from "../components/ProfileMain.vue";
// import HelloWorld from "../components/HelloWorld.vue";
import HistoryTable from '../components/HistoryTable.vue';
import axiosAuth from '@/api/axios-auth'

export default {
  name: 'profil-page',
  components: {
    ProfileMain,
    HistoryTable,
  },
  methods: {
    loadHisto() {
      const path = `${process.env.VUE_APP_BACKEND_URL}/history`
      axiosAuth.get(path).then((res)=> {
        this.entries = res.data.entries
      })
    }
  },
  computed: {
    ...mapGetters('auth', {
      isAuth: 'isAuthenticated',
      id: 'getID',
      username: 'getUsername'
    })
  },
  props: ['current_route'],
  data() {
      return {
          url:process.env.VUE_APP_BACKEND_URL,
          histo:false,
          edit:true,
          entries: [],
      }
  },
};
</script>

<style scoped>
.pp {
  height:125px;
  width:125px;
  border-radius:50%;
}

.active {
  color:aqua;
}

a {
  color:rgb(255, 255, 255);
  text-decoration: bold;
}
</style>
