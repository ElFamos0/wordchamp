<template>
  <div class="profil">
    <b-row class="justify-content-md-center">
      <b-col cols="4"></b-col>
      <b-col cols="4">
        <b-avatar variant="primary" v-bind:src="url + '/avatar/' + id" size="100px"></b-avatar>
      </b-col>
      <b-col cols="5"></b-col>
    </b-row>
    <div class="mb-4" id="nav">
      <b-nav tabs class="justify-content-md-center">
          <b-nav-item> <a href="#" :class="{ 'router-link-exact-active': edit }" @click="edit=true; histo=false"> Modifier Profil </a></b-nav-item>
          <b-nav-item> <a href="#" :class="{ 'router-link-exact-active': histo }" @click="edit=false; histo=true"> Historique </a></b-nav-item>
      </b-nav>
    </div>          
    <profile-main v-if="edit"></profile-main>
    <hello-world v-if="histo"></hello-world>
  </div>
</template>

<script>
import { mapGetters } from 'vuex';
import ProfileMain from "../components/ProfileMain.vue";
import HelloWorld from "../components/HelloWorld.vue";

export default {
  name: 'profil-page',
  components: {
    ProfileMain,
    HelloWorld
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
</style>
