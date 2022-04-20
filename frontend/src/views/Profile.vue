<template>
  <div class="profil">
    <b-avatar variant="primary" v-bind:src="url + '/avatar/' + id" size="100px"></b-avatar>

    <p><b>{{ username }}</b></p>
    <div id="nav">
      <b-nav tabs class="justify-content-md-center">
          <b-nav-item> <router-link to="/profile"> Modifier Profil </router-link></b-nav-item>
          <b-nav-item> <router-link to="/profile/historique"> Historique </router-link></b-nav-item>
      </b-nav>
    </div>
    <router-view/>
  </div>
</template>

<script>
import { mapGetters } from 'vuex';
export default {
  name: 'profil-page',

  computed: {
    ...mapGetters('auth', {
      isAuth: 'isAuthenticated',
      id: 'getID',
      username: 'getUsername'
    })
  },
  data() {
      return {
          url:process.env.VUE_APP_BACKEND_URL,
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
</style>
