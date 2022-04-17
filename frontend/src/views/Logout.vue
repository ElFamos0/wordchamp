<template>
    <div>
    </div>
</template>

<script>
export default {
    name: 'logOut',
    created() {
        this.$store.dispatch('auth/logout', this.form);
        this.$router.push('/');
    }
}
</script>