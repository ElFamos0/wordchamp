<!-- Template de la navigation seulement ! -->

<template>
  <div id="app">
    <div id="nav">
      <router-link to="/">Home</router-link> |
      <router-link to="/random">Random</router-link> |
      <tag v-if="isAuth">
        <router-link to="/word">Play</router-link> |
      </tag>
      <tag v-if="!isAuth">
        <router-link to="/login">Login</router-link> |
      </tag>
      <tag v-if="isAuth">
        <router-link to="/logout"> Logout </router-link> |
      </tag>
      <router-link to="/register">Register</router-link>
    </div>
    <router-view/>
  </div>
</template>

<script>
import { mapGetters } from 'vuex'
export default {
  name: 'App',
  created() {
    this.$store.dispatch('auth/autoLogin');
  },
  computed: {
    ...mapGetters('auth', {
      isAuth: 'isAuthenticated',
    })
  },
  methods: {
    onLogout() {
      this.$store.dispatch('auth/logout');
    }
  }
}
</script>


<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
}

#nav {
  padding: 30px;
}

#nav a {
  font-weight: bold;
  color: #2c3e50;
}

#nav a.router-link-exact-active {
  color: #42b983;
}
</style>
